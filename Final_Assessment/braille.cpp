/*****************************************/
/* Task:        Project 2-1, Part 1      */
/* Course:      CVI620                   */
/* Student:     Yathavan Parameshwaran   */
/* Date:        April 16, 2020           */
/* Professor:   Vida Movahedi            */
/*****************************************/

#include <iostream>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>

int main()
{
    cv::Mat sub1, bumps_mat, holes_mat, sub1_grey, sub2_grey;

    cv::namedWindow("sub1_window");
    cv::namedWindow("bumps_window");
    cv::namedWindow("holes_window");

    sub1 = cv::imread("project_files_dir/Project_2_1_files/SAM1_sub1.jpg", cv::IMREAD_ANYCOLOR);
    bumps_mat = cv::imread("project_files_dir/Project_2_1_files/SAM1_sub1.jpg", cv::IMREAD_ANYCOLOR);
    holes_mat = cv::imread("project_files_dir/Project_2_1_files/SAM1_sub1.jpg", cv::IMREAD_ANYCOLOR);

    cv::cvtColor(sub1, sub1_grey, cv::COLOR_BGR2GRAY);

    cv::blur(sub1_grey, sub1_grey, cv::Size(3, 3));
    cv::threshold(sub1_grey, sub1_grey, 150, 255, cv::THRESH_BINARY);
    cv::Canny(sub1_grey, sub1_grey, 120, 255);

    /* right now, after running edge detection, you can more prominently see the differences b/w bumps and holes */
    /* the holes are more "circular" as it in an indentation INTO the material... the bumps are much more "flatter" (and have a greater width) becauseo of the large shadow UNDERNEATH each bump */
    /* all i need to do is figure out a way to differenciate b/w the circles and the ovals (oblongs?) and i should be good */

    /* update #2 */
    /* 
        4:37am... haven't slept in 36 hours... roti has gone stale...

        Bump and hole detection is working perfectly. The trick was to isolate the area of each contour and if it is less than or greater than the median of all the bumps and holes.
        This works because each bump is identical, and each hole is identical.
        So all bumps will be "grouped" similarly in area and all holes will be grouped similarly in area as well. It all comes down to splitting it correctly and then evaluating. Luckily in my case the splitting point was right down the middle. 
    */
    
    std::vector<std::vector<cv::Point>> bumps_and_holes;
    std::vector<std::vector<cv::Point>> bumps;
    std::vector<std::vector<cv::Point>> holes;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(
        sub1_grey,
        bumps_and_holes,
        hierarchy,
        cv::RETR_TREE,
        cv::CHAIN_APPROX_SIMPLE
    );

    std::cout << "Total # of bumps/holes: " << bumps_and_holes.size() << std::endl;

    std::vector<float> widths;
    std::vector<float> widths_sorted;

    for (int index = 0; index < bumps_and_holes.size(); index++)
    {
        cv::RotatedRect contour = cv::minAreaRect(bumps_and_holes[index]);

        widths.push_back(contour.size.area());
    }

    widths_sorted = widths;
    std::sort(widths_sorted.begin(), widths_sorted.end());
    float median = widths_sorted.at(widths.size() / 2);

    for (int i = 0; i < widths.size(); i++)
    {
        float width = widths.at(i);
        
        if (width <= median)
        {
            holes.push_back(bumps_and_holes.at(i));
        }
        else
        {
            bumps.push_back(bumps_and_holes.at(i));
        }
    }

    cv::drawContours(bumps_mat, bumps, -1, cv::Scalar(0,255,0), 1);
    cv::drawContours(holes_mat, holes, -1, cv::Scalar(0,0,255), 1);

    cv::imwrite("sub1_window.jpg", sub1_grey);
    cv::imwrite("bumps_window.jpg", bumps_mat);
    cv::imwrite("holes_window.jpg", holes_mat);

    // while (1)
    // {
    //     int keycode = cv::waitKey(0);
    //     if (keycode == 113)
    //     {
    //         exit(0);
    //     }
    //     else
    //     {
    //         std::cout << "press 'q' to exit!" << std::endl;
    //     }
    // }

    return 0;
}
