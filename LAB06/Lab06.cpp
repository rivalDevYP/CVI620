/* 

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy.  We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>

int main()
{
    cv::Mat macbookImg, grey_macbookImg;

    // opening image
    macbookImg = cv::imread("macbook.jpg", cv::IMREAD_COLOR);
    cv::resizeWindow("macbook", 1348, 758);
    cv::imshow("macbook", macbookImg);
    cv::waitKey(1000);

    // converting to greyscale
    cv::cvtColor(macbookImg, grey_macbookImg, cv::COLOR_BGR2GRAY);
    cv::imwrite("grey_macbook.jpg", grey_macbookImg);
    cv::imshow("grey_macbook", grey_macbookImg);
    cv::waitKey(1000);

    // converting greyscale img to binary image
    cv::Mat binary_img;
    cv::threshold(grey_macbookImg, binary_img, 128, 255, cv::THRESH_BINARY);
    cv::imwrite("binary_image.jpg", binary_img);
    cv::imshow("binary_image", binary_img);
    cv::waitKey(1000);

    // adding morphological opening to binary image using 3x3 kernel
    cv::Mat kernel_one = 255 * cv::Mat::ones(3, 3, CV_8UC1);

    cv::Mat morphology_open_img_3;
    cv::morphologyEx(binary_img, morphology_open_img_3, cv::MORPH_OPEN, kernel_one);
    cv::imwrite("morphology_open_img_3.jpg", morphology_open_img_3);
    cv::imshow("morphology_open_img_3", morphology_open_img_3);
    cv::waitKey(1000);

    // apply morphological closing to binary image using 3x3 kernel
    cv::Mat morphology_close_img_3;
    cv::morphologyEx(binary_img, morphology_close_img_3, cv::MORPH_CLOSE, kernel_one);
    cv::imwrite("morphology_close_img_3.jpg", morphology_close_img_3);
    cv::imshow("morphology_close_img_3", morphology_close_img_3);
    cv::waitKey(1000);

    // adding morphological opening to binary image using 7x7 kernel
    cv::Mat kernel_two = 255 * cv::Mat::ones(7, 7, CV_8UC1);

    cv::Mat morphology_open_img_7;
    cv::morphologyEx(binary_img, morphology_open_img_7, cv::MORPH_OPEN, kernel_two);
    cv::imwrite("morphology_open_img_7.jpg", morphology_open_img_7);
    cv::imshow("morphology_open_img_7", morphology_open_img_7);
    cv::waitKey(1000);

    // apply morphological closing to binary image using 7x7 kernel
    cv::Mat morphology_close_img_7;
    cv::morphologyEx(binary_img, morphology_close_img_7, cv::MORPH_CLOSE, kernel_two);
    cv::imwrite("morphology_close_img_7.jpg", morphology_close_img_7);
    cv::imshow("morphology_close_img_7", morphology_close_img_7);
    cv::waitKey(1000);

    return 0;
}