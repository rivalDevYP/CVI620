/*

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy. We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <vector>
#include <numeric>

cv::Mat generateNoise(cv::Mat &incomingImage, float incomingNoisePercentage)
{
    cv::Mat noisyImg = incomingImage;
    cv::Mat x(incomingImage.rows, incomingImage.cols, CV_32FC1);
    cv::RNG rngObj;
    rngObj.fill(x, cv::RNG::UNIFORM, 0.0f, 1.0f);
    for (int rowIter = 0; rowIter < incomingImage.rows; rowIter++)
    {
        for (int colIter = 0; colIter < incomingImage.cols; colIter++)
        {
            if (x.at<float>(rowIter, colIter) < incomingNoisePercentage)
            {
                float y = rngObj.uniform(0.0f, 1.0f);
                
                cv::Vec3b &pixel = noisyImg.at<cv::Vec3b>(rowIter, colIter);

                pixel[0]  = 0 + (y * (255 - 0));
                pixel[1]  = 0 + (y * (255 - 0));
                pixel[2]  = 0 + (y * (255 - 0));
            }
        }
    }

    return noisyImg;
}

int main()
{
    float userProbabilityInput = 0.0;

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
    cv::imwrite("noisy_image.jpg", noisyImage);
    cv::imshow("noisy image", noisyImage);
    cv::waitKey(1000);

    // c. Smooth the above noisy image using a 3 x 3 box kernel. Display the blurred image.

    cv::Mat smoothedImage;
    cv::blur(noisyImage, smoothedImage, cv::Size(3, 3));
    cv::imwrite("smoothed_image.jpg", smoothedImage);
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

    std::cout << "\nPrinting blue values of pixel at (500,500) and it's neighbors from NOISY IMAGE..." << std::endl;
    for (std::vector<short>::iterator i = blueVals.begin(); i != blueVals.end(); i++)
    {
        std::cout << *i << std::endl;
    }

    // Calculate what you expect for the blurred pixel value.

    std::cout.precision(15);
    std::cout << "I predict that the blurred pixel value will be " << std::accumulate(blueVals.begin(), blueVals.end(), 0) << "/" << blueVals.size() << " = " << std::fixed << (std::accumulate(blueVals.begin(), blueVals.end(), (double)0) / blueVals.size()) << std::endl;

    blueVals.clear();

    // Then check the value for the blurred image. Are they the same?

    std::cout << "\nBlue value of pixel at (500,500) from SMOOTHED IMAGE: "<< (short)smoothedImage.at<cv::Vec3b>(pos1, pos2)[0] << std::endl;


    // e. Filter the above noisy image using a 3 x 3 bilinear filter and display the result.

    cv::Mat filteredImage;
    cv::Matx<float, 3, 3> myKernel = cv::Matx<float, 3, 3>::all((1 / 16.0f));
    cv::filter2D(noisyImage, filteredImage, CV_8U, myKernel);
    cv::imwrite("box_filtered_image.jpg", filteredImage);
    cv::imshow("box filtered image", filteredImage);
    cv::waitKey(1000);

    // f. De-noise the noisy image using a median filter and display the resulting image.

    cv::Mat medianFilteredImg;
    cv::medianBlur(noisyImage, medianFilteredImg, 3);
    cv::imwrite("median_filtered_image.jpg", medianFilteredImg);
    cv::imshow("median filtered image", medianFilteredImg);
    cv::waitKey(1000);

    // g. Compare the results of the above filters. Which filter works better for de-noising?

    return 0;
}