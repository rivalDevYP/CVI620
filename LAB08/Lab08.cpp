/*

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy. We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <vector>
#include <numeric>

/** calculate precision and recall for a binary classifier which classifies a target as belonging to a class (true) or not (false) */
int calcPR(bool *pred, bool *gt, int len, double *P, double *R)
{
}

/** calculate Fβ */
double calcFb(double P, doubleR, double beta)
{
}

/** read CSV files */
void readCSV(std::string incomingFileName)
{
}

/** convert the response of a continuous classifier (A) to a Boolean response (B) given a threshold (thresh) */
void thresh_v(double *A, bool *B, int len, double thresh)
{
    // If the response value is more than the threshold, convert it to true; otherwise, convert to false.
}

/** Write a function to read the continuous response in alg_dbl.csv */
void readResponse()
{
}

/** converts an image to a Boolean array. If the pixel value is more than a threshold, convert it to true; otherwise, convert to false */
void thresh_img(Mat img, bool *B, double thresh)
{
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    return 0;
}