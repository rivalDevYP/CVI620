package cvi.finalproject.dicedetector;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.Dimension;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.textview.MaterialTextView;

import org.opencv.android.BaseLoaderCallback;
import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.JavaCamera2View;
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
import org.opencv.videoio.VideoCapture;

import java.util.List;
import java.util.Vector;

public class DiceDetector extends Fragment implements CameraBridgeViewBase.CvCameraViewListener2
{
    private static String TAG = "MainActivity";

    private VideoCapture captureModule;
    private Mat standardImage, greyScaleImage;
    private MaterialTextView totalDice, oneCount, twoCount, threeCount, fourCount, fiveCount, sixCount;
    private CameraBridgeViewBase cvCameraView;
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

    BaseLoaderCallback baseLoaderCallback = new BaseLoaderCallback(this.getContext())
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
        View view = inflater.inflate(R.layout.view_cam, container, false);

        totalDice = view.findViewById(R.id.diceCountTextView);
        oneCount = view.findViewById(R.id.onesCountTextView);
        twoCount = view.findViewById(R.id.twosCountTextView);
        threeCount = view.findViewById(R.id.threesCountTextView);
        fourCount = view.findViewById(R.id.foursCountTextView);
        fiveCount = view.findViewById(R.id.fivesCountTextView);
        sixCount = view.findViewById(R.id.sixesCountTextView);

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
        int diceCount = 0;

        mRGBA = inputFrame.rgba();
        mGRAY = inputFrame.gray();

        mRGBAT = mRGBA.t();
        mGRAYT = mGRAY.t();

        Core.flip(mRGBA.t(), mRGBAT, 1);
        Core.flip(mGRAY.t(), mGRAYT, 1);

        Imgproc.resize(mRGBAT, mRGBAT, mRGBA.size());
        Imgproc.resize(mGRAYT, mGRAYT, mGRAY.size());

        Log.d(TAG, "blur to reduce noise");
        Size blurKernel = new Size(3,3);
        Imgproc.blur(mGRAYT, mGRAYT, blurKernel);

        Log.d(TAG,"binary thresholding");
        Imgproc.threshold(mGRAYT, mGRAYT, 170, 255, Imgproc.THRESH_BINARY);

        Log.d(TAG,"perform edge detection");
        Imgproc.Canny(mGRAYT, mGRAYT, 80, 230);

        Log.d(TAG,"finding contours");
        Vector<MatOfPoint> contours = new Vector<>();
        MatOfInt4 hierarchy = new MatOfInt4();
        Imgproc.findContours(mGRAYT, contours, hierarchy, Imgproc.RETR_TREE, Imgproc.CHAIN_APPROX_SIMPLE);

        Log.d(TAG,"find minimum area rectangles");
        Vector<RotatedRect> diceRects = new Vector<>();
        for (int index = 0; index < contours.size(); index++)
        {
            Log.d(TAG,"for each contour, search minimum area rectangle");
            MatOfPoint2f matOfPoint2f = new MatOfPoint2f();
            contours.elementAt(index).convertTo(matOfPoint2f, CvType.CV_32S);
            RotatedRect rotatedRect = Imgproc.minAreaRect(matOfPoint2f);

            Log.d(TAG,"process only rectangles that are almost square and of right side");
            float aspect = Math.abs((float) (rotatedRect.size.height / rotatedRect.size.width) - 1);
            if ((aspect < 0.25) && (rotatedRect.size.area() > 2000) && (rotatedRect.size.area() < 4000))
            {
                Log.d(TAG,"check for duplicate rectangles");
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

                    Log.d(TAG,"draw square over each dice");
                    for (int jug = 0; jug < 4; jug++)
                    {
                        Scalar mScalar = new Scalar(0,0,255);
                        Imgproc.line(mRGBAT, points[jug], points[(jug + 1) % 4], mScalar, 2, Imgproc.LINE_AA);
                    }
                }
            }
        }

//        totalDice.setText(diceRects.size());

//        return mRGBAT;

        return mGRAYT;
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
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION, this.getContext(), baseLoaderCallback);
        }
    }
}