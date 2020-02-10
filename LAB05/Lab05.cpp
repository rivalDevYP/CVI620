/*

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy. We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

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

    std::cout << "Blue value of pixel at (" << pos1 - 1 << ", " << pos2 - 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 - 1 << ", " << pos2 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 - 1 << ", " << pos2 + 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 << ", " << pos2 - 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 << ", " << pos2 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 << ", " << pos2 + 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 + 1 << ", " << pos2 - 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 + 1 << ", " << pos2 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    std::cout << "Blue value of pixel at (" << pos1 + 1 << ", " << pos2 + 1 << "): " << (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;

    // Calculate what you expect for the blurred pixel value. 

    

    // Then check the value for the blurred image. Are they the same?

    // e. Filter the above noisy image using a 3 x 3 bilinear filter and display the result.

    // f. De-noise the noisy image using a median filter and display the resulting image.

    // g. Compare the results of the above filters. Which filter works better for de-noising?

    return 0;
}