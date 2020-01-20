// Example 2-10. The same object can load videos from a camera or a file
//
#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <string>
#include <dirent.h>

#define HEIGHT 480
#define WIDTH 640

int main()
{
    cv::Mat black_box(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(0, 0, 0));
    bool input_not_valid = true;
    double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;
    cv::viz::Color selectedColor;
    char userColorSelection = '\0';

    while (input_not_valid)
    {
        std::cout << "please enter a coordinate for x1: ";
        std::cin >> x1;
        if (x1 < 0 || x1 > HEIGHT)
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
        std::cout << "please enter a coordinate for y1: ";
        std::cin >> y1;
        if (y1 < 0 || y1 > HEIGHT)
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
        std::cout << "please enter a coordinate for x2: ";
        std::cin >> x2;
        if (x2 < 0 || x2 > HEIGHT)
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
        std::cout << "please enter a coordinate for y2: ";
        std::cin >> y2;
        if (y2 < 0 || y2 > HEIGHT)
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
    std::cout << x1 << std::endl;
    std::cout << x2 << std::endl;
    std::cout << y1 << std::endl;
    std::cout << y2 << std::endl;

    std::cout << "Please specify a color..." << std::endl;
    std::cin >> userColorSelection;

    switch (userColorSelection)
    {
    case 'k':
        selectedColor = cv::viz::Color::black();
    case 'w':
        selectedColor = cv::viz::Color::white();
    case 'r':
        selectedColor = cv::viz::Color::red();
    case 'g':
        selectedColor = cv::viz::Color::green();
    case 'b':
        selectedColor = cv::viz::Color::blue();
    case 'c':
        selectedColor = cv::viz::Color::cyan();
    case 'y':
        selectedColor = cv::viz::Color::yellow();
    case 'm':
        selectedColor = cv::viz::Color::magenta();
    case 'x':
        selectedColor = cv::Scalar(rand() % 255, rand() % 255);
    };

//     Black (0, 0, 0)
// Red (0, 0, 255)
// Green (0, 255, 0)
// Blue (255, 0, 0)
// Yellow (0, 255, 255)
// Magenta (255, 0, 255)
// Cyan (255, 255, 0)
// White (255, 255, 255)

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