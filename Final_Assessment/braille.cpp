/*****************************************/
/* Task:        Project 2-1, Part 1      */
/* Course:      CVI620                   */
/* Student:     Yathavan Parameshwaran   */
/* Date:        April 16, 2020           */
/* Professor:   Vida Movahedi            */
/*****************************************/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

int main ()
{
    cv::Mat sub1, sub2, sub1_grey, sub2_grey;

    cv::namedWindow("sub1_window");
    cv::namedWindow("sub2_window");

    sub1 = cv::imread("project_files_dir/Project_2_1_files/SAM1_sub1.jpg", cv::IMREAD_ANYCOLOR);
    sub2 = cv::imread("project_files_dir/Project_2_1_files/SAM1_sub1.jpg", cv::IMREAD_ANYCOLOR);

    cv::cvtColor(sub1, sub1_grey, cv::COLOR_BGR2GRAY);
    cv::cvtColor(sub2, sub2_grey, cv::COLOR_BGR2GRAY);

    cv::blur(sub1_grey, sub1_grey, cv::Size(3,3));
    cv::threshold(sub1_grey, sub1_grey, 150, 255, cv::THRESH_BINARY);
    cv::Canny(sub1_grey, sub1_grey, 120, 255);

    cv::imshow("sub1_window", sub1_grey);
    cv::imshow("sub2_window", sub2_grey);

    while(1)
    {
        int keycode = cv::waitKey(0);
        if (keycode == 120)
        {
            exit(0);
        }
        else
        {
            std::cout << "press 'x' to exit!" << std::endl;
        }
    }
    


    

    return 0;
}
