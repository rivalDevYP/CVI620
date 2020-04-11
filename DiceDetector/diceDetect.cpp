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
		cv::threshold(greyImage, greyImage, averageLightValue - 25, 255, cv::THRESH_BINARY);
		cv::Canny(greyImage, greyImage, averageLightValue, 255);

		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::findContours(
			greyImage,
			contours,
			hierarchy,
			cv::RETR_TREE,
			cv::CHAIN_APPROX_SIMPLE
		);

		std::vector<cv::RotatedRect> diceRects;
		for (int i = 0; i < contours.size(); i++)
		{
			cv::RotatedRect rect = cv::minAreaRect(contours[i]);

			float aspect = fabs(rect.size.aspectRatio() - 1);
			if ((aspect < 0.25) && (rect.size.area() > 2000) && (rect.size.area() < 4000))
			{
				bool process = true;
				for (int j = 0; j < diceRects.size(); j++)
				{
					float dist = cv::norm(rect.center - diceRects[j].center);
					if (dist < 10)
					{
						process = false;
						break;
					}
				}

				if (process)
				{
					diceRects.push_back(rect);
					cv::Point2f points[4];
					rect.points(points);
					for (int j = 0; j < 4; j++)
					{
						cv::line(
							myImg,
							points[j],
							points[(j + 1) % 4],
							cv::Scalar(0, 255, 0),
							2,
							cv::LINE_AA);
					}
				}
			}
		}

		char buffer[32];
		sprintf(buffer, "Dice: %d", (int) diceRects.size());
		cv::putText(
			myImg,
			buffer,
			cv::Point(20, 30),
			cv::FONT_HERSHEY_PLAIN,
			0.8,
			cv::Scalar(0,255,0),
			1,
			cv::LINE_AA
		);

		int diceCounts[6] = {
			0,0,0,0,0,0
		};

		for (int i = 0; i < diceRects.size(); i++)
		{
			cv::Mat rotation, rotated, cropped;
			cv::RotatedRect rect = diceRects[i];
			rotation = cv::getRotationMatrix2D(
				rect.center,
				rect.angle,
				1.0
			);
			cv::warpAffine(
				greyImage,
				rotated,
				rotation,
				greyImage.size(),
				cv::INTER_CUBIC
			);
			cv::getRectSubPix(
				rotated,
				cv::Size(
					rect.size.width - 10,
					rect.size.height - 10
				),
				rect.center,
				cropped
			);
			std::vector<std::vector<cv::Point>> dieContours;
			std::vector<cv::Vec4i> dieHierarchy;
			cv::threshold(
				cropped,
				cropped,
				64,
				255,
				cv::THRESH_BINARY
			);
			cv::findContours(
				cropped,
				dieContours,
				dieHierarchy,
				cv::RETR_TREE,
				cv::CHAIN_APPROX_SIMPLE
			);
			std::vector<cv::RotatedRect> dotsRects;
			for (int i = 0; i < dieContours.size(); i++)
			{
				cv::RotatedRect dotRect = cv::minAreaRect(dieContours[i]);
				float aspect = fabs(dotRect.size.aspectRatio() - 1);
				if ((aspect < 0.4) && (dotRect.size.area() > 8) && (dotRect.size.area() < 150))
				{
					bool process = true;
					for (int j = 0; j < dotsRects.size(); j++)
					{
						float dist = cv::norm(dotRect.center - dotsRects[j].center);
						if (dist < 10)
						{
							process = false;
							break;
						}
					}

					if (process)
					{
						dotsRects.push_back(dotRect);
					}
				}
			}

			if (dotsRects.size() >= 1 && dotsRects.size() <= 6)
			{
				diceCounts[dotsRects.size() - 1]++;
			}
		}

		for (int i = 1; i < 6; i++)
		{
			int count = 0;
			for (int j = i; i < 6; i++)
			{
				count += diceCounts[j];
			}
			sprintf(buffer, "%d+: %d", (i+1), count);
			cv::putText(
				myImg,
				buffer,
				cv::Point(20, 55 + 25 * i),
				cv::FONT_HERSHEY_PLAIN,
				0.8,
				cv::Scalar(
					0,
					255,
					0
				),
				1,
				cv::LINE_AA
			);			
		}

		cv::imshow("rgb_window", myImg);
		cv::imshow("grey_window", greyImage);
		// cv::imshow("hsv_window", drawing);

		int i = cv::waitKey(1);

		if (i != -1)
		{
			break;
			// exit(0);
		}
	}
}
