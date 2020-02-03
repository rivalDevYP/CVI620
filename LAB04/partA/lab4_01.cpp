/**********************/
/* CVI620             */
/* Lab 04             */
/* Group 7            */
/* January 27, 2020   */
/**********************/

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

//using namespace cv;
//using namespace std;

int main(int argc, char** argv) {

	bool input_not_valid = true;
	bool quitOption = false;
	char userOption = '\0';
	double alpha = 0.00;

	while (!quitOption) {
		// validate menu option
		while (input_not_valid) // input menu option 
		{
			// asking user for color choice
			std::cout << "Enter option (a) sharpen and brighten image, (b) linear blend 2 images and calculate histogram or (q) to quit: ";
			std::cin >> userOption;

			if (userOption == 'a' || userOption == 'b') {
				break;
			}
			if (userOption == 'q') {
				quitOption = true;
				break;
			}
		}

		if (!quitOption) {
			cv::Mat image, mod_img, //image for part1
				image1, image2,  //images for part 2 - linear blend
				//dst, //matrix for loading 2 images into 1 window
				b_hist; //histogram for the colour blue (part2)
			
			//load images
			image = cv::imread(cv::samples::findFile("fruits.jpg"));
			image1 = cv::imread(cv::samples::findFile("LinuxLogo.jpg"));
			image2 = cv::imread(cv::samples::findFile("WindowsLogo.jpg"));
			// image = cv::imread("fruits.jpg");
			// image2 = cv::imread("WindowsLogo.jpg");
			// image1 = cv::imread("LinuxLogo.jpg");

			//cv::Mat dst(image1.rows*2, image1.cols, CV_8UC3, cv::Scalar(0, 0, 0));
			//cv::Rect roi(cv::Rect(0, 0, image1.cols, image1.rows));
			//cv::Mat targetROI = dst(roi);
			//image1.copyTo(targetROI);
			//targetROI = dst(cv::Rect(0, image1.rows, image1.cols, image1.rows));
			//image2.copyTo(targetROI);


			if (image.empty()) // Check for invalid input
			{
				std::cout << "Could not open or find the image" << std::endl;
				return -1;
			}
			if (image1.empty()) {
				std::cout << "Could not open or find the image" << std::endl;
				return -1;
			}
			if (image2.empty()) {
				std::cout << "Could not open or find the image" << std::endl;
				return -1;
			}

			switch (userOption) {
			case 'a':
				//a. open original image
				cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
				cv::imshow("Original image", image); // Show our image inside it.
				std::cout << "Original image: R(" << (int)image.at<cv::Vec3b>(50, 50)[2] << ") G(" << (int)image.at<cv::Vec3b>(50, 50)[1] << ") B(" << (int)image.at<cv::Vec3b>(50, 50)[0] << ")" << std::endl;
				//cv::waitKey(0); // Wait for a keystroke in the window + update image

				//b. increase brightness		
				image.copyTo(mod_img);
				mod_img += cv::Scalar(100, 100, 100);
				cv::namedWindow("Brightened image", cv::WINDOW_AUTOSIZE);
				cv::imshow("Brightened image", mod_img); // Show our image inside it.
				std::cout << "Brightened image: R(" << (int)mod_img.at<cv::Vec3b>(50, 50)[2] << ") G(" << (int)mod_img.at<cv::Vec3b>(50, 50)[1] << ") B(" << (int)mod_img.at<cv::Vec3b>(50, 50)[0] << ")" << std::endl;
				//cv::waitKey(0); // Wait for a keystroke in the window + update image

				//c. increase contrast / sharpness
				image.copyTo(mod_img); //reset mod_img
				mod_img *= 1.5;
				cv::namedWindow("Sharpened image", cv::WINDOW_AUTOSIZE);
				cv::imshow("Sharpened image", mod_img); // Show our image inside it.
				std::cout << "Sharpened image: R(" << (int)mod_img.at<cv::Vec3b>(50, 50)[2] << ") G(" << (int)mod_img.at<cv::Vec3b>(50, 50)[1] << ") B(" << (int)mod_img.at<cv::Vec3b>(50, 50)[0] << ")" << std::endl;
				cv::waitKey(0);
				cv::destroyAllWindows();
				break;

			case 'b':
				cv::namedWindow("Image1", cv::WINDOW_AUTOSIZE);
				cv::imshow("Image1", image1);
				cv::namedWindow("Image2", cv::WINDOW_AUTOSIZE);
				cv::imshow("Image2", image2);
				cv::waitKey(0);

				while (input_not_valid) // alpha input
				{
					// asking user for color choice
					std::cout << "Enter a number between 0 and 1: ";
					std::cin >> alpha;

					if (alpha >= 0.0 && alpha <= 1.0) {
						break;
					}
				}								

				cv::Mat blend = (1 - alpha) * image1 + alpha * image2;
				cv::imshow("Linear Blend", blend);
				cv::waitKey(0);

				//display calcHist results
				std::vector<cv::Mat> brg; //matrix for blue red green
				split(image1, brg);
				int histSize = 256; //from 0-255
				float range[] = {0, 256};
				const float* histRange = { range };
				int hist_w = 512; int hist_h = 400;
				int bin_w = cvRound((double)hist_w / histSize);
				
				cv::calcHist(&brg[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, &histRange, 
					true, //histogram is uniform
					false); //histogram is not accumalated
				

				double maxVal = 0;
				cv::minMaxLoc(b_hist, 0, &maxVal, 0, 0);

				int intensity[8]{};
				int bin = -1;
				for (int i = 0; i < histSize; i++) {
					if (i % 32 == 0) {
						bin++;
					}
					float binVal = b_hist.at<float>(i);
					intensity[bin] += binVal;
				}
				for (int b = 0; b < 8; b++) {
					std::cout << "Bin [" << b*32 << " - "<< (b+1)*32-1<< "], Intensity: " << intensity[b] << std::endl;
				}

				cv::waitKey(0);
				cv::destroyAllWindows();

				image.release();
				image1.release();
				image2.release();
				break;

			}
		}
	}

	return 0;
}