/*

We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached assignment is our own work in accordance with the Seneca Academic Policy. We have not copied any part of this assignment, manually or electronically, from any other source including web sites, unless specified as references. We have not distributed our work to other students.

*/

#include <iostream>
#include <fstream>
#include <string>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <vector>
#include <numeric>
#include <cmath>

int myFileLength = 0;

/** calculate precision and recall for a binary classifier which classifies a target as belonging to a class (true) or not (false) */
int calcPR(bool *pred, bool *gt, int len, double *P, double *R)
{
    // Inputs:
    //      pred: pointer to classifier predictions
    //      gt: pointer to ground truth classes
    //          ground truth: perfect answer
    //      len: length of pred and gt arrays
    // Outputs:
    //      P: pointer to return precision
    //      R: pointer to return recall
    //
    //      Return 1 if successful, 0 otherwise

    // Instructions:
    //      Write a loop and go through all elements of pred and gt;
    //      update values of TP, FP, etc.
    //      e.g:
    //          if (*(pred + j) && !(*(gt + j)))
    //          {
    //              FP++;
    //          }
    //      Then use formulas from class to calculate precision and recall

    // recall = tp / (tp + fn)
    // precision = tp / (tp + fp)

    // TP (true positives):
    //     Number of samples identified correctly as belonging to a class/ category
    // FP (false positive): (false alarms!)
    //     Number of samples identified incorrectly as belonging to a class / category
    // TN (true negative):
    //     Number of samples identified correctly as NOT belonging to a class/ category
    // FN (false negatives):
    //     Number of samples identified incorrectly as NOT belonging to a class/ category

    try
    {
        // Total number of samples = TP + FP + TN + FN

        int TP{0}, FP{0}, TN{0}, FN{0};

        // loop through classifier predictions and ground truth classes

        // std::cout << "reached" << std::endl;

        for (int index = 0; index < 19; index++)
        {
            if ((*(pred + index)) && !(*(gt + index)))
            {
                FP++;
            }
            if ((*(pred + index)) && (*(gt + index)))
            {
                TP++;
            }
            if (!(*(pred + index)) && (*(gt + index)))
            {
                TN++;
            }
            if (!(*(pred + index)) && !(*(gt + index)))
            {
                FN++;
            }
        }

        // recall = tp / (tp + fn)
        // precision = tp / (tp + fp)

        *R = (double) TP / (TP + FN);
        *P = (double) TP / (TP + FP);

        return 1;
    }
    catch (...)
    {
        return 0;
    }
}

/** calculate Fβ */
double calcFb(double P, double R, double beta)
{
    // Fβ = (1 + (β^2)) * (P*R) / ((β^2) * P) + R
    double answer = (1 + pow(beta, 2)) * (P * R) / (pow(beta, 2) * P) + R;

    return answer;
}

/** read CSV files (added by student) */
bool *readCSV(std::string incomingFileName)
{
    /*
        Write function(s) to read alg_bin.csv as the classifier predictions and gt.csv as the 
        ground truth. In these files, each row belongs to a data sample. The value ‘1’ means 
        belonging to the class (true), while ‘0’ means not belonging to the class (false).
    */

    std::ifstream csv_file(incomingFileName);

    int i = 0;
    bool readLine = '\0';

    // read the file to get length of the file
    if (csv_file.is_open())
    {
        while (!csv_file.eof())
        {
            csv_file >> readLine;
            myFileLength++;
        }
    }

    myFileLength = myFileLength - 1; // because of the extra blank line in the file

    // initialize array to store file's data
    static bool fileData[20];

    // go back to beginning of file
    csv_file.clear();
    csv_file.seekg(0, std::ios::beg);

    // read file again, this time storing the data in the array
    if (csv_file.is_open())
    {
        for (int i = 0; i < myFileLength; i++)
        {
            csv_file >> fileData[i];
        }
    }

    return fileData;
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
void thresh_img(cv::Mat img, bool *B, double thresh)
{
}

void evalBinClass()
{
    double P, R;
    if (calcPR(readCSV("alg_bin.csv"), readCSV("gt.csv"), 20, &P, &R))
    {
        std::cout << "Part I: F1= " << std::fixed << std::setprecision(4) << calcFb(P, R, 1) << std::endl;
    }
}

void evalBinContRes()
{

}

void evalImgBasClass()
{

}

void evalImgBasClassContRes()
{
    
}

int main()
{
    int userSelection = 0;

    std::cout << "Please select one of the following options: " << std::endl;
    std::cout << "\n(1) Evaluating a binary classifier"
              << "\n(2) Evaluating a binary classifier with a continuous response"
              << "\n(3) Evaluating image-based classifiers"
              << "\n(4) Evaluating image-based classifiers with continuous responses"
              << "\n(5) Exit Program"
              << std::endl;

    std::cout << "Please enter a selection: ";
    std::cin >> userSelection;

    switch (userSelection)
    {
    case 1:
        evalBinClass();
        break;
    case 2:
        evalBinContRes();
        break;
    case 3:
        evalImgBasClass();
        break;
    case 4:
        evalImgBasClassContRes();
        break;
    case 5:
        std::cout << "exiting program" << std::endl;
        exit(0);
    default:
        std::cout << "You have entered an incorrect option...\n";
        break;
    }

    return 0;
}