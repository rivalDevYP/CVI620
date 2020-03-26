// We, (Gabriella Ko, Patrick O'reilly, Yathavan Parameshwaran), declare that the attached 
// assignment is our own work in accordance with the Seneca Academic Policy. We have not 
// copied any part of this assignment, manually or electronically, from any other source 
// including web sites, unless specified as references. We have not distributed our work 
// to other students.

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

        for (int index = 0; index < len; index++)
        {
            if ((*(pred + index)) && !(*(gt + index)))
            {
                FP++;
            }
            else if ((*(pred + index)) && (*(gt + index)))
            {
                TP++;
            }
            else if (!(*(pred + index)) && (*(gt + index)))
            {
                FN++;
            }
            else if (!(*(pred + index)) && !(*(gt + index)))
            {
                TN++;
            }
        }

        // recall = tp / (tp + fn)
        // precision = tp / (tp + fp)

        *R = (double)TP / (TP + FN);
        *P = (double)TP / (TP + FP);

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
    return (1 + pow(beta, 2)) * ((P * R) / ((pow(beta, 2) * P) + R));
}

void readBooleanCSV(std::string incomingFileName, bool *incomingPtr)
{
    std::ifstream csv_file(incomingFileName);

    if (csv_file.is_open())
    {
        int i = 0;
        while (!csv_file.eof() && i < 20)
        {
            csv_file >> incomingPtr[i++];
        }
    }
}

void readDoubleDSV(std::string incomingFileName, double *incomingPtr)
{
    std::ifstream csv_file(incomingFileName);

    static double d_buffer[19];

    if (csv_file.is_open())
    {
        int i = 0;
        while (!csv_file.eof())
        {
            csv_file >> incomingPtr[i++];
        }
    }
}

/** convert the response of a continuous classifier (A) to a Boolean response (B) given a threshold (thresh) */
void thresh_v(double *A, bool *B, int len, double thresh)
{
    // If the response value is more than the threshold, convert it to true; otherwise, convert to false.
    for (int i = 0; i < len; i++)
    {
        *(B + i) = (*(A + i)) > thresh;
    }
}

/** Write a function to read the continuous response in alg_dbl.csv */
void readResponse()
{
}

/** converts an image to a Boolean array. If the pixel value is more than a threshold, convert it to true; otherwise, convert to false */
void thresh_img(cv::Mat img, bool *B, double thresh)
{
    // *(B + j) = (*(A + j) > thresh);
    for (int k = 0; k < 10; k++)
    {
        for (int j = 0; j < 10; j++)
        {
            for (int i = 0; i < 10; i++)
            {
                
            }
        }
    }
}

// Part I: Evaluating a binary classifier
void option_1()
{
    const unsigned int len = 20;
    double P{0.0}, R{0.0};

    bool *ptr1 = new bool[len];
    bool *ptr2 = new bool[len];

    readBooleanCSV("alg_bin.csv", ptr1);
    readBooleanCSV("gt.csv", ptr2);

    if (calcPR(ptr1, ptr2, len, &P, &R))
    {
        std::cout << "Part I: F1= " << std::fixed << std::setprecision(4) << calcFb(P, R, 1) << "\n\n"
                  << std::endl;
    }
    else
    {
        std::cout << "\nerror while performing evaluation...\n"
                  << std::endl;
    }

    delete[] ptr1;
    delete[] ptr2;
}

// Part II: Evaluating a binary classifier with a continuous response
void option_2()
{
    const int csv_len{20};
    const int thres_len{9};

    double F1{0.0}, P{0}, R{0}, selectedThreshold{0.0};
    double threshold[thres_len] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    bool *ptr1 = new bool[csv_len];
    bool *ptr2 = new bool[csv_len];
    double *threshold_arr_ptr = new double[csv_len];

    std::ofstream pr_csv_file;
    pr_csv_file.open("PR.csv");

    readBooleanCSV("alg_bin.csv", ptr1);
    readBooleanCSV("gt.csv", ptr2);
    readDoubleDSV("alg_dbl.csv", threshold_arr_ptr);

    for (int index = 0; index < thres_len; index++)
    {
        thresh_v(threshold_arr_ptr, ptr1, thres_len, threshold[index]);
        thresh_v(threshold_arr_ptr, ptr2, thres_len, threshold[index]);
        if (calcPR(ptr1, ptr2, csv_len, &P, &R))
        {
            double fb = calcFb(P, R, 1);
            pr_csv_file << fb << "," << threshold[index] << std::endl;
            if (fb > F1)
            {
                F1 = fb;
                selectedThreshold = threshold[index];
            }
        }
        else
        {
            std::cout << "Error calculating PR..." << std::endl;
        }        
    }

    std::cout << "Part II: max F1 = " << F1 << " at threshold = " << selectedThreshold << std::endl;

    delete[] ptr1;
    delete[] ptr2;
    delete[] threshold_arr_ptr;
}

// Part III: Evaluating image-based classifiers
void option_3()
{
    cv::Mat bitmap_A1 = cv::imread("bitmap_A1.png", cv::IMREAD_GRAYSCALE);
    cv::Mat bitmap_gt = cv::imread("bitmap_gt.png", cv::IMREAD_GRAYSCALE);

    int numberOfPixels = bitmap_A1.total() > bitmap_gt.total() ? bitmap_A1.total() : bitmap_gt.total(); // go for whichever is higher...

    bool* bitmap_A1_arr = new bool[numberOfPixels];
    bool* bitmap_gt_arr = new bool[numberOfPixels];


}

// Part IV: Evaluating image-based classifiers with continuous responses
void option_4()
{
}

int main()
{
    while (1)
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
            option_1();
            continue;
        case 2:
            option_2();
            continue;
        case 3:
            option_3();
            continue;
        case 4:
            option_4();
            continue;
        case 5:
            std::cout << "exiting program" << std::endl;
            exit(0);
        default:
            std::cout << "You have entered an incorrect option...\n";
            continue;
        }

        fflush(stdin);
    }

    return 0;
}