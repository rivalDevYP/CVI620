/**********************/
/* CVI620             */
/* Lab 03             */
/* Group 7            */
/* January 20, 2020   */
/**********************/

#include <opencv2/opencv.hpp>
#include <opencv2/core/types.hpp>
#include <iostream>
#include <string>
#include <cstdio>
#include <thread>

#define HEIGHT 480
#define WIDTH 640

int main()
{
    cv::Mat black_box(HEIGHT, WIDTH, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::imshow("black", black_box);
    cv::waitKey(1000);

    while (1)
    {
        bool input_not_valid = true;
        double x1 = 0.0, x2 = 0.0, y1 = 0.0, y2 = 0.0;
        std::string x1_y1_str = "", x2_y2_str = "";
        cv::Vec3b selectedColor;
        char userColorSelection = '\0';

        // ask for top left corner coordinates; keep asking until valid
        while (input_not_valid) // x1y1 input
        {
            std::cout << "Enter the coordinates of the top left corner (x y): ";
            std::fflush(stdin);
            std::getline(std::cin, x1_y1_str);            
            x1 = std::stod(x1_y1_str.substr(0, x1_y1_str.find(' ')));
            y1 = std::stod(x1_y1_str.substr(x1_y1_str.find(' ')));

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

        // ask for bottom right corner coordinates; keep asking until valid
        while (input_not_valid) // x2y2 input
        {
            std::cout << "Enter the coordinates of the bottom right corner (x y): ";
            std::fflush(stdin);
            std::getline(std::cin, x2_y2_str);
            x2 = std::stod(x2_y2_str.substr(0, x2_y2_str.find(' ')));
            y2 = std::stod(x2_y2_str.substr(x2_y2_str.find(' ')));

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

        // asking user for color choice
        std::cout << "Enter a letter for color (x:random, r:red, g:green, b:blue, k:black, w:white, y:yellow, c:cyan, m:magenta): ";
        std::cin >> userColorSelection;

        // setting the color choice
        switch (userColorSelection)
        {
        case 'k':
            selectedColor = cv::Vec3b(0, 0, 0);
        case 'w':
            selectedColor = cv::Vec3b(255, 255, 255);
        case 'r':
            selectedColor = cv::Vec3b(0, 0, 255);
        case 'g':
            selectedColor = cv::Vec3b(0, 255, 0);
        case 'b':
            selectedColor = cv::Vec3b(255, 0, 0);
        case 'c':
            selectedColor = cv::Vec3b(255, 255, 0);
        case 'y':
            selectedColor = cv::Vec3b(0, 255, 255);
        case 'm':
            selectedColor = cv::Vec3b(255, 0, 255);
        case 'x':
            selectedColor = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
        };

        // coloring the pixels as specified by the user
        for (int index = y1; index < y2; index++)
        {
            for (int index2 = x1; index2 < x2; index2++)
            {
                cv::Vec3b &color = black_box.at<cv::Vec3b>(index, index2);

                color = selectedColor;
            }
        }

        // refresh the view to show the colored pixels
        cv::imshow("black", black_box);
        cv::waitKey(1000);

        // Define a ‘Rect’ object and set the members with the coordinates given by the user in step (i). 
        // Then use the member functions to print the area, width, and height of the rectangle. 
        // Check the values. Are they correct?

        cv::Point pt1(x1, y1);
        cv::Point pt2(x2, y2); 
        cv::Rect rectObj1(pt1, pt2);

        std::cout << "Area of Rect object: " << rectObj1.area() << std::endl;
        std::cout << "Width of Rect object: " << rectObj1.width << std::endl;
        std::cout << "Height of Rect object: " << rectObj1.height << std::endl;


        // Ask for the coordinates of a point (px, py). 
        // Then use the member functions of above Rect object to print if this point is inside of the rectangle or not. 

        std::string x3_y3_str = "";
        int x3 = 0, y3 = 0;

        std::cin.ignore();
        std::cout << "Please enter the coordinates for a point (x y): ";
        std::fflush(stdin);
        std::getline(std::cin, x3_y3_str);

        x3 = std::stod(x3_y3_str.substr(0, x3_y3_str.find(' ')));
        y3 = std::stod(x3_y3_str.substr(x3_y3_str.find(' ')));

        cv::Point pt3(x3, y3);

        if (rectObj1.contains(pt3))
        {
            std::cout << "The rectangle contains the point specified at " << x3 << ", " << y3 << std::endl;
        }
        else
        {
            std::cout << "The rectangle DOES NOT contain the point specified at " << x3 << ", " << y3 << std::endl;
        }

        // if user wishes to continue, keep going to loop around
        // if not, then save the image as Lab03.jpg
        char ch = '\0';
        std::cout << "Continue (y/n)? ";
        std::cin >> ch;
        if (ch != 'y')
        {
            // save the iamge as Lab03.jpg
            cv::imwrite("Lab03.jpg", black_box);
            exit(0);
        }

        std::cin.ignore();
    }
}