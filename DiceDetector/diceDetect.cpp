#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main ()
{
	cv::VideoCapture videoCaptureModule;
	videoCaptureModule.open(0);

	cv::namedWindow("DisplayWindow");

	while (1) // infinite loop
	{
		// capturing video from webcam
		cv::Mat myImg;
		videoCaptureModule.read(myImg);

		// discard color values (greyscale) to maximize edge detection
		cv::Mat greyImage;
		cv::cvtColor(myImg, greyImage, cv::COLOR_BGR2GRAY);

		// window that will show video output
		cv::namedWindow("ComputationWindow");

		// blur to reduce noise
		cv::blur(greyImage, greyImage, cv::Size(3,3));

		// binary thresholding
		cv::threshold(greyImage, greyImage, 170, 255, cv::THRESH_BINARY);

		// perform edge detection
		cv::Canny(greyImage, greyImage, 80, 230);

		// find contours
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(greyImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

		// finding minimum area rectangles
		std::vector<cv::RotatedRect> diceRects;
		for (int index = 0; index < contours.size(); index++)
		{
			// for each contour, search minimum area rectangle
			cv::RotatedRect rotatedRect = cv::minAreaRect(contours[index]);
			diceRects.push_back(rotatedRect);

			// draw square over each dice
			cv::Point2f points[4];
			rotatedRect.points(points);

			for (int juggernaut = 0; juggernaut < 4; juggernaut++)
			{
				cv::line(myImg, points[juggernaut], points[(juggernaut + 1) % 4], cv::Scalar(0,0,255), 2, cv::LINE_AA);
			}
		}

		// write dice count on screen
		char buffer[25];
		sprintf(buffer, "Dice: %d", (int) diceRects.size());
		cv::putText(myImg, buffer, cv::Point(20, 30), cv::FONT_HERSHEY_DUPLEX, 0.8, cv::Scalar(0,255,0), 1, cv::LINE_AA);

		// displaying grey image in ComputationWindow
		cv::imshow("ComputationWindow", greyImage);

		int i = cv::waitKey(1);

		if (i != -1)
		{
			break;
		}
	}
}
