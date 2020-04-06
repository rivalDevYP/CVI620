package cvi.finalproject.dicedetector;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.textview.MaterialTextView;

import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;
import org.opencv.videoio.VideoCapture;

public class DiceDetector extends Fragment
{
    private VideoCapture captureModule;
    private Mat standardImage, greyScaleImage;
    private MaterialTextView totalDice, oneCount, twoCount, threeCount, fourCount, fiveCount, sixCount;

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

        launchDiceDetection();

        return view;
    }

    private void launchDiceDetection()
    {
        // launch video feed as color
        // display color video feed
        // convert video feed to b&w
        // blur video feed
        // binary thresholding
        // perform edge detection (Imgproc.Canny();)
        // find contours
        // find min-area rectangles
        // filter rectangles w/ different size of a die
        // count dots on each die
        // update numbers on UI
    }
}
