package cvi.finalproject.dicedetector;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.RotateAnimation;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.textview.MaterialTextView;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.JavaCameraView;
import org.opencv.android.OpenCVLoader;
import org.opencv.core.Core;
import org.opencv.core.CvType;
import org.opencv.core.Mat;
import org.opencv.core.MatOfInt4;
import org.opencv.core.MatOfPoint;
import org.opencv.core.MatOfPoint2f;
import org.opencv.core.Point;
import org.opencv.core.RotatedRect;
import org.opencv.core.Scalar;
import org.opencv.core.Size;
import org.opencv.imgproc.Imgproc;

import java.util.Vector;

public class DiceDetector extends Fragment implements CameraBridgeViewBase.CvCameraViewListener2
{
    private static String TAG = "MainActivity";
    private Context myContext;
    private MaterialTextView totalDice, oneCount, twoCount, threeCount, fourCount, fiveCount, sixCount, sumCount, averageCount;
    private JavaCameraView javaCameraView;
    private Mat mRGBA, mRGBAT, mGRAY, mGRAYT;

    static
    {
//        if (OpenCVLoader.initDebug())
//        {
//            Log.d(TAG, "OpenCV is configured or connected successfully");
//        }
//        else
//        {
//            Log.d(TAG, "OpenCV not working or loaded");
//        }
    }

    BaseLoaderCallback baseLoaderCallback = new BaseLoaderCallback(myContext)
    {
        @Override
        public void onManagerConnected(int status)
        {
            switch (status)
            {
                case BaseLoaderCallback.SUCCESS: {
                    javaCameraView.enableView();
                    break;
                }
                default: {
                    break;
                }
            }
            super.onManagerConnected(status);
        }
    };

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState)
    {
        myContext = getActivity();

        View view = inflater.inflate(R.layout.view_cam, container, false);

        totalDice = view.findViewById(R.id.diceCountTextView);
        oneCount = view.findViewById(R.id.onesCountTextView);
        twoCount = view.findViewById(R.id.twosCountTextView);
        threeCount = view.findViewById(R.id.threesCountTextView);
        fourCount = view.findViewById(R.id.foursCountTextView);
        fiveCount = view.findViewById(R.id.fivesCountTextView);
        sixCount = view.findViewById(R.id.sixesCountTextView);
        sumCount = view.findViewById(R.id.sumTextView);
        averageCount = view.findViewById(R.id.averageSumTextView);

        javaCameraView = view.findViewById(R.id.cameraView);
        javaCameraView.setVisibility(SurfaceView.VISIBLE);
        javaCameraView.setCvCameraViewListener(this);

        return view;
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        if (javaCameraView != null)
        {
            javaCameraView.disableView();
        }
    }

    @Override
    public void onCameraViewStarted(int width, int height)
    {
        Log.e("Info", "Camera started!");
        mRGBA = new Mat(height, width, CvType.CV_8UC4);
        mGRAY = new Mat(height, width, CvType.CV_8UC1);
    }

    @Override
    public void onCameraViewStopped()
    {
        mGRAY.release();
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame)
    {
        mRGBA = inputFrame.rgba();
        mGRAY = inputFrame.gray();

        mRGBAT = mRGBA.t();
        mGRAYT = mGRAY.t();

        Core.flip(mRGBA.t(), mRGBAT, 1);
        Core.flip(mGRAY.t(), mGRAYT, 1);

        Imgproc.resize(mRGBAT, mRGBAT, mRGBA.size());
        Imgproc.resize(mGRAYT, mGRAYT, mGRAY.size());

        // blur to reduce noise
        Size blurKernel = new Size(3,3);
        Imgproc.blur(mGRAYT, mGRAYT, blurKernel);

        // binary thresholding
        Imgproc.threshold(mGRAYT, mGRAYT, 170, 255, Imgproc.THRESH_BINARY);

        // perform edge detection
        Imgproc.Canny(mGRAYT, mGRAYT, 80, 230);

        // finding contours
        Vector<MatOfPoint> contours = new Vector<>();
        MatOfInt4 hierarchy = new MatOfInt4();
        Imgproc.findContours(mGRAYT, contours, hierarchy, Imgproc.RETR_TREE, Imgproc.CHAIN_APPROX_SIMPLE);

        int[] diceCounts = new int[6];

        for (int i = 0; i < 6; i++)
        {
            diceCounts[i] = 0;
        }

        // find minimum area rectangles
        Vector<RotatedRect> diceRects = new Vector<>();
        for (int index = 0; index < contours.size(); index++)
        {
            // for each contour, search minimum area rectangle
            MatOfPoint2f matOfPoint2f = new MatOfPoint2f(contours.elementAt(index).toArray());
            RotatedRect rotatedRect = Imgproc.minAreaRect(matOfPoint2f);

            // process only rectangles that are almost square and of right side
            float aspect = Math.abs((float) (rotatedRect.size.width / rotatedRect.size.height) - 1);
            if ((aspect < 0.25) && (rotatedRect.size.area() > 1000) && (rotatedRect.size.area() < 4000))
            {
                // check for duplicate rectangles
                boolean process = true;
                for (int spartan = 0; spartan < diceRects.size(); spartan++)
                {
                    Point pt1 = rotatedRect.center;
                    Point pt2 = diceRects.elementAt(spartan).center;

                    float dist = (float) (Math.sqrt(pt1.x * pt1.y) - Math.sqrt(pt2.x * pt2.y));

                    if (dist < 10)
                    {
                        process = false;
                        break;
                    }
                }
                if (process)
                {
                    diceRects.add(rotatedRect);
                    Point[] points = new Point[4];
                    rotatedRect.points(points);

                    // draw square over each dice
                    for (int jug = 0; jug < 4; jug++)
                    {
                        Scalar mScalar = new Scalar(0,255,0);
                        Imgproc.line(mRGBAT, points[jug], points[(jug + 1) % 4], mScalar, 2, Imgproc.LINE_AA);
                    }

                    // counting the dots on each die
                    for (int dotIter = 0; dotIter < diceRects.size(); dotIter++)
                    {
                        // extract die image
                        Mat rotation = new Mat();
                        Mat rotated = new Mat();
                        Mat cropped = new Mat();

                        RotatedRect rect = diceRects.elementAt(dotIter);

                        rotation = Imgproc.getRotationMatrix2D(rect.center, rect.angle, 1.0);

                        Imgproc.warpAffine(mGRAYT, rotated, rotation, mGRAYT.size(), Imgproc.INTER_CUBIC);

                        Size mySize = new Size(rect.size.width - 10, rect.size.height - 10);

                        Imgproc.getRectSubPix(rotated, mySize, rect.center, cropped);

                        // find contours
                        Vector<MatOfPoint> die_contours = new Vector<>();
                        MatOfInt4 die_hierarchy = new MatOfInt4();
                        Imgproc.threshold(cropped, cropped, 64, 255, Imgproc.THRESH_BINARY);
                        Imgproc.findContours(cropped, die_contours, die_hierarchy, Imgproc.RETR_TREE, Imgproc.CHAIN_APPROX_SIMPLE);

                        // find and filter minimum area rects
                        Vector<RotatedRect> dotsRects = new Vector<>();
                        for (int dotIter_2 = 0; dotIter_2 < die_contours.size(); dotIter_2++)
                        {
                            MatOfPoint2f matOfPoint2f1 = new MatOfPoint2f(die_contours.elementAt(dotIter_2).toArray());
                            RotatedRect dotRect = Imgproc.minAreaRect(matOfPoint2f1);

                            float aspect2 = Math.abs((float) (dotRect.size.width / dotRect.size.height) - 1);
                            if ((aspect2 < 0.4) && (dotRect.size.area() > 8) && (dotRect.size.area() < 150))
                            {
                                // check if duplicate rect
                                boolean process2 = true;
                                for (int jug2 = 0; jug2 < dotsRects.size(); jug2++)
                                {
                                    Point ptr1 = dotRect.center;
                                    Point ptr2 = dotsRects.elementAt(jug2).center;

                                    float dist_dot = (float) ((Math.sqrt(ptr1.x * ptr1.y)) - Math.sqrt(ptr2.x * ptr2.y));

                                    if (dist_dot < 10)
                                    {
                                        process2 = false;
                                        break;
                                    }
                                }

                                if (process2)
                                {
                                    dotsRects.add(dotRect);
                                }
                            }
                        }
                        // save dots counts

                        if (dotsRects.size() >= 1 && dotsRects.size() <= 6)
                        {
                            diceCounts[dotsRects.size() - 1]++;
                        }
                    }
                }
            }

            try
            {
                inputFrame.wait(2000);
            } catch (InterruptedException ex)
            {
                Log.d(TAG, "Interrupted Exception caught!");
            }
        }

        setDiceText(diceRects.size(), diceCounts[0],diceCounts[1],diceCounts[2],diceCounts[3],diceCounts[4],diceCounts[5]);


        return mRGBAT;
    }

    @SuppressLint("SetTextI18n")
    private void setDiceText(int totalDiceCount, int one, int two, int three, int four, int five, int six)
    {
        int sum =(one) + (two * 2) + (three * 3) + (four * 4) + (five * 5) + (six * 6);

        totalDice.setText(Integer.toString(totalDiceCount));
        oneCount.setText(Integer.toString(one));
        twoCount.setText(Integer.toString(two));
        threeCount.setText(Integer.toString(three));
        fourCount.setText(Integer.toString(four));
        fiveCount.setText(Integer.toString(five));
        sixCount.setText(Integer.toString(six));
        sumCount.setText(Integer.toString(sum));
        averageCount.setText(Integer.toString(sum / totalDiceCount));
    }

    @Override
    public void onPause()
    {
        super.onPause();
        if (javaCameraView != null)
        {
            javaCameraView.disableView();
        }
    }

    @Override
    public void onResume()
    {
        super.onResume();
        if (OpenCVLoader.initDebug())
        {
            Log.d(TAG, "OpenCV is configured or connected successfully");
            baseLoaderCallback.onManagerConnected(BaseLoaderCallback.SUCCESS);
        }
        else
        {
            Log.d(TAG, "OpenCV not working or loaded");
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION, myContext, baseLoaderCallback);
        }
    }
}