/*

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy. We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <vector>
#include <numeric>

/* code for generateNoise acquired from 'A Practical Introduction to COMPUTER VISION WITH OPENCV by Kenneth Dawson-Howe' */
cv::Mat &generateNoise(cv::Mat &incomingImage, double incomingNoisePercentage)
{
    int imageRows = incomingImage.rows;
    int imageColumns = incomingImage.cols;
    int imageChannels = incomingImage.channels();

    int noisePoints = (int)(((double)imageRows * imageColumns * imageChannels) * incomingNoisePercentage / 100.0);

    for (int index = 0; index < noisePoints; index++)
    {
        int row = rand() % imageRows;
        int column = rand() % imageColumns;
        int channel = rand() % imageChannels;

        uchar *pixel = incomingImage.ptr<uchar>(row) + (column * imageChannels) + channel;

        *pixel = (rand() % 2 == 1) ? 255 : 0;
    }

    return incomingImage;
}

int main()
{
    double userProbabilityInput = 0.0;

    // a. Open a color image and display.

    cv::Mat myImage;
    myImage = cv::imread("dell_latitude.jpg", cv::IMREAD_COLOR);
    cv::namedWindow("dell latitude", cv::WINDOW_AUTOSIZE);
    cv::imshow("dell latitude", myImage);
    cv::waitKey(1000);

    // b. Ask for a probability value between 0 and 1, and implement the salt and pepper noise with the given probability. Create a noisy image with p=0.1. Display the noisy image.

    std::cout << "Please enter a probability between 0 and 1: ";
    std::cin >> userProbabilityInput;
    cv::Mat noisyImage = generateNoise(myImage, userProbabilityInput);
    cv::imshow("noisy image", noisyImage);
    cv::waitKey(1000);

    // c. Smooth the above noisy image using a 3 x 3 box kernel. Display the blurred image.

    cv::Mat smoothedImage;
    cv::blur(noisyImage, smoothedImage, cv::Size(3, 3));
    cv::imshow("smoothed image", smoothedImage);
    cv::waitKey(1000);

    // d. Choose a pixel and output the pixel’s blue value, as well as its neighbors’.

    int pos1 = 500, pos2 = 500;
    std::vector<short> blueVals;
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 - 1, pos2 - 1)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 - 1, pos2)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 - 1, pos2 + 1)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1, pos2 - 1)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1, pos2)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1, pos2 + 1)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 + 1, pos2 - 1)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 + 1, pos2)[0]);
    blueVals.push_back((short)noisyImage.at<cv::Vec3b>(pos1 + 1, pos2 + 1)[0]);

    std::cout << "Printing blue values of pixel at (500,500) and it's neighbors from NOISY IMAGE..." << std::endl;
    for (std::vector<short>::iterator i = blueVals.begin(); i != blueVals.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    // Calculate what you expect for the blurred pixel value.

    std::cout.precision(15);
    std::cout << "I predict that the blurred pixel value will be " << std::accumulate(blueVals.begin(), blueVals.end(), 0) << "/" << blueVals.size() << " = " << std::fixed << (std::accumulate(blueVals.begin(), blueVals.end(), (double)0) / blueVals.size()) << std::endl;

    // Then check the value for the blurred image. Are they the same?

    blueVals.clear();

    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 - 1, pos2 - 1)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 - 1, pos2)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 - 1, pos2 + 1)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1, pos2 - 1)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1, pos2 + 1)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 + 1, pos2 - 1)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 + 1, pos2)[0]);
    blueVals.push_back((short)smoothedImage.at<cv::Vec3b>(pos1 + 1, pos2 + 1)[0]);

    std::cout << "\n\nPrinting blue values of pixel at (500,500) and it's neighbors from SMOOTHED IMAGE..." << std::endl;
    for (std::vector<short>::iterator i = blueVals.begin(); i != blueVals.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    // e. Filter the above noisy image using a 3 x 3 bilinear filter and display the result.

    cv::Mat filteredImage;
    cv::Matx<float, 3, 3> myKernel = cv::Matx<float, 3, 3>::all(1 / 9.0f);
    cv::filter2D(noisyImage, filteredImage, CV_8U, myKernel);
    cv::imshow("box filtered image", filteredImage);
    cv::waitKey(1000);

    // f. De-noise the noisy image using a median filter and display the resulting image.

    cv::Mat medianFilteredImg;
    cv::medianBlur(noisyImage, medianFilteredImg, 3);
    cv::imshow("median filtered image", medianFilteredImg);
    cv::waitKey(1000);

    // g. Compare the results of the above filters. Which filter works better for de-noising?

    return 0;
}