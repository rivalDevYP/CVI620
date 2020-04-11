#include <iostream>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

int main()
{
	cv::VideoCapture videoCaptureModule;
	videoCaptureModule.open(0);

	// cv::namedWindow("rgb_window");
	cv::namedWindow("grey_window");
	// cv::namedWindow("hsv_window");

	while (1) // infinite loop
	{
		// capturing video from webcam
		cv::Mat myImg;
		cv::Mat greyImage;
		// cv::Mat hsvImage;

		videoCaptureModule.read(myImg);

		cv::pyrMeanShiftFiltering(greyImage, greyImage, 20, 40, 3);
		cv::cvtColor(myImg, greyImage, cv::COLOR_BGR2GRAY);
		// cv::cvtColor(myImg, hsvImage, cv::COLOR_BGR2HLS);

		long totalValue = 0;

		// calculate total value of all pixels (GRAY)
		for (int i = 0; i < greyImage.rows; i++)
		{
			for (int j = 0; j < greyImage.cols; j++)
			{
				totalValue += greyImage.at<uchar>(i, j);
				// greyImage.at<uchar>(i, j) = (greyImage.at<uchar>(i, j)) * ;
			}
		}

		// calculate average light value
		int averageLightValue = totalValue / greyImage.total();

		cv::blur(greyImage, greyImage, cv::Size(7, 7));
		// cv::morphologyEx(greyImage, greyImage, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3)));
		// cv::threshold(greyImage, greyImage, averageLightValue - 25, 255, cv::THRESH_BINARY);
		// cv::Canny(greyImage, greyImage, averageLightValue, 255);

		// std::vector<std::vector<cv::Point>> contours;
		// std::vector<cv::Vec4i> hierarchy;

		// cv::findContours(greyImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
		// void HoughCircles(InputArray image, OutputArray circles, int method, double dp, double minDist, double param1=100, double param2=100, int minRadius=0, int maxRadius=0 )
		// HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 2, gray->rows/4, 200, 100 );
		std::vector<cv::Vec3f> circles;

		/* void cv::HoughCircles(
			cv::InputArray image, 		// image – 8-bit, single-channel, grayscale input image.
			cv::OutputArray circles, 	// circles – Output vector of found circles. Each vector is encoded as a 3-element floating-point vector (x, y, radius) .
			int method, 				// method – Detection method to use. Currently, the only implemented method is CV_HOUGH_GRADIENT , which is basically 21HT , described in [Yuen90].
			double dp, 					// dp – Inverse ratio of the accumulator resolution to the image resolution. For example, if dp=1 , the accumulator has the same resolution as the input image. If dp=2 , the accumulator has half as big width and height.
			double minDist, 			// minDist – Minimum distance between the centers of the detected circles. If the parameter is too small, multiple neighbor circles may be falsely detected in addition to a true one. If it is too large, some circles may be missed.
			double param1 = (100.0), 	// param1 – First method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the higher threshold of the two passed to the Canny() edge detector (the lower one is twice smaller).
			double param2 = (100.0), 	// param2 – Second method-specific parameter. In case of CV_HOUGH_GRADIENT , it is the accumulator threshold for the circle centers at the detection stage. The smaller it is, the more false circles may be detected. Circles, corresponding to the larger accumulator values, will be returned first.
			int minRadius = 0, 			// minRadius – Minimum circle radius.
			int maxRadius = 0 			// maxRadius – Maximum circle radius.
		) 
		*/

		cv::HoughCircles(
			greyImage,			// image
			circles,			// circles
			cv::HOUGH_GRADIENT, // method
			1,					// dp
			0.1,				// minDist
			80,					// param1
			20,					// param2
			0.1,				// minRadius
			40);				// maxRadius

		// cv::Mat drawing = cv::Mat::zeros(greyImage.size(), CV_8UC3);
		// cv::RNG rng(12345);
		std::vector<cv::Point2f> centerPoints;
		for (int i = 0; i < circles.size(); i++)
		{
			// cv::Scalar color = cv::Scalar(0, 255, 0);
			// cv::drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
			cv::Point center(cvRound(circles.at(i)[0]), cvRound(circles.at(i)[1]));
			centerPoints.push_back(center);
			int radius = cvRound(circles.at(i)[2]);
			// 	// draw the circle center
			circle(myImg, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
			// draw the circle outline
			circle(myImg, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
		}

		printf("\nCircles: %d", circles.size());
		cv::Mat clusterCenters;

		// double compactness = cv::kmeans(
		// 	centerPoints,
		// 	circles.size(),
		// 	greyImage,
		// 	cv::TermCriteria(
		// 		cv::TermCriteria::EPS + cv::TermCriteria::COUNT,
		// 		10,
		// 		1.0),
		// 	3,
		// 	cv::KMEANS_PP_CENTERS,
		// 	clusterCenters);

		// char buffer[32];
		// sprintf(buffer, "Contours: %d", contours.size());
		// cv::putText(greyImage, buffer, cv::Point(20, 20), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0), 2, 8, false);

		cv::imshow("rgb_window", myImg);
		// cv::imshow("grey_window", greyImage);
		// cv::imshow("hsv_window", drawing);

		int i = cv::waitKey(1);

		if (i != -1)
		{
			// break;
			exit(0);
		}
	}
}
