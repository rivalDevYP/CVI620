// Example 2-10. The same object can load videos from a camera or a file
//
#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <string>
#include <cstdio>

#define HEIGHT 480
#define WIDTH 640

int main()
{
    cv::Mat black_box(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(0, 0, 0));
    bool input_not_valid = true;
    double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;
    std::string x1_str = "", y1_str = "", x2_str = "", y2_str = "";
    cv::Vec3b selectedColor;
    char userColorSelection = '\0';

    while (input_not_valid)
    {
        std::cout << "Enter the coordinates of the top left corner (x y): ";
        std::cin >> x1_str >> y1_str;
        x1 = std::stod(x1_str);
        y1 = std::stod(y1_str);
        
        if ((x1 < 0 || x1 > HEIGHT) || (y1 < 0 || y1 > HEIGHT))
        {
            std::cout << "ERROR => please enter a valid value" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    while (input_not_valid)
    {
        std::cout << "Enter the coordinates of the bottom right corner (x y): ";
        std::cin >> x2_str >> y2_str;
        x1 = std::stod(x2_str);
        y1 = std::stod(y2_str);
        
        if ((x2 < 0 || x2 > HEIGHT) || (y2 < 0 || y2 > HEIGHT))
        {
            std::cout << "ERROR => please enter a valid value" << std::endl;
            continue;
        }
        else
        {
            break;
        }
    }

    /* FOR TESTING PURPOSES, REMOVE BEFORE FINAL SUBMISSION */
    // std::cout << x1 << std::endl;
    // std::cout << x2 << std::endl;
    // std::cout << y1 << std::endl;
    // std::cout << y2 << std::endl;

    std::cout << "Enter a letter for color (x:random, r:red, g:green, b:blue, k:black, w:white, y:yellow, c:cyan, m:magenta): ";
    std::cin >> userColorSelection;

    switch (userColorSelection)
    {
    case 'k':
        selectedColor = cv::Vec3b(0, 0, 0);
    case 'w':
        selectedColor = cv::Vec3b(0, 0, 255);
    case 'r':
        selectedColor = cv::Vec3b(0, 255, 0);
    case 'g':
        selectedColor = cv::Vec3b(255, 0, 0);
    case 'b':
        selectedColor = cv::Vec3b(0, 255, 255);
    case 'c':
        selectedColor = cv::Vec3b(255, 0, 255);
    case 'y':
        selectedColor = cv::Vec3b(255, 255, 0);
    case 'm':
        selectedColor = cv::Vec3b(255, 255, 255);
    case 'x':
        selectedColor = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
    };

    for (int index = y1; index < y2; index++)
    {
        for (int index2 = x1; index2 < x2; index2++)
        {
            cv::Vec3b& color = black_box.at<cv::Vec3b>(index, index2);

            color = selectedColor;
        }
    }

    cv::imshow("black",black_box);
    cv::waitKey(0);
}