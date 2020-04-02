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
	// Total number of samples = TP + FP + TN + FN
	int TP = 0, FP = 0, TN = 0, FN = 0;

	try
	{
		// loop through classifier predictions and ground truth classes
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
		if (TP == 0 && FP == 0)
		{
			*P = (double)1;
		}
		else
		{
			*P = (double)TP / (TP + FP);
		}

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

void readDoubleCSV(std::string incomingFileName, double *incomingPtr)
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

/** converts an image to a Boolean array. If the pixel value is more than a threshold, convert it to true; otherwise, convert to false */
void thresh_img(cv::Mat img, bool *B, double thresh)
{
	for (int j = 0; j < img.rows; j++)
	{
		for (int i = 0; i < img.cols; i++)
		{
			*(B++) = (img.at<uchar>(j, i) > thresh);
		}
	}
}

// Part I: Evaluating a binary classifier
void option_1()
{
	const unsigned int len = 20;
	double P = 0.0, R = 0.0;

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
	const int csv_len = 20;
	const int thres_len = 9;

	double F1 = 0.0, P = 0.0, R = 0.0, selectedThreshold = 0.0;
	double threshold[thres_len] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

	bool *ptr1 = new bool[csv_len];
	bool *ptr2 = new bool[csv_len];
	double *continuous_response_ptr = new double[csv_len];

	std::ofstream pr_csv_file;
	pr_csv_file.open("PR.csv");

	readBooleanCSV("alg_bin.csv", ptr1);
	readBooleanCSV("gt.csv", ptr2);
	readDoubleCSV("alg_dbl.csv", continuous_response_ptr);

	for (int index = 0; index < thres_len; index++)
	{
		thresh_v(continuous_response_ptr, ptr1, csv_len, threshold[index]);
		// thresh_v(continuous_response_ptr, ptr2, csv_len, threshold[index]);
		if (calcPR(ptr1, ptr2, csv_len, &P, &R))
		{
			double fb = calcFb(P, R, 1);
			pr_csv_file << P << "," << R << std::endl;
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
	delete[] continuous_response_ptr;
}

// Part III: Evaluating image-based classifiers
void option_3()
{
	const double threshVal = 128.00;

	// opening png images
	cv::Mat bitmap_A1 = cv::imread("bitmap_A1.png", cv::IMREAD_GRAYSCALE);
	cv::Mat bitmap_gt = cv::imread("bitmap_gt.png", cv::IMREAD_GRAYSCALE);

	// boolean arrays that store binary arrays of above images
	bool *bitmap_A1_arr = new bool[bitmap_A1.total()];
	bool *bitmap_gt_arr = new bool[bitmap_gt.total()];

	double P = 0.0, R = 0.0;

	// picture to binary arr with threshold of 128
	thresh_img(bitmap_A1, bitmap_A1_arr, threshVal);
	thresh_img(bitmap_gt, bitmap_gt_arr, threshVal);

	if (calcPR(bitmap_A1_arr, bitmap_gt_arr, bitmap_A1.total(), &P, &R)) // BUG: returns diff values b/w 1st and subsequent iterations
	{
		std::cout << "Part III: F1 = " << std::fixed << std::setprecision(4) << calcFb(P, R, 1) << std::endl;
	}

	delete[] bitmap_A1_arr;
	delete[] bitmap_gt_arr;
}

// Part IV: Evaluating image-based classifiers with continuous responses
void option_4()
{
	const int csv_len = 20;
	const int threshold_val_len = 10;

	const double threshVal_A2 = 125.00;
	const double threshVal_GT = 128.00;

	double F1 = 0.0, selectThresh = 0.0, P = 0.0, R = 0.0;

	double thresholdValues[threshold_val_len];
	double *cont_res_ptr = new double[csv_len];

	cv::Mat bitmap_A2 = cv::imread("bitmap_A2.png", cv::IMREAD_GRAYSCALE);
	cv::Mat bitmap_GT = cv::imread("bitmap_gt.png", cv::IMREAD_GRAYSCALE);

	bool *bitmap_A2_arr = new bool[bitmap_A2.total()];
	bool *bitmap_GT_arr = new bool[bitmap_GT.total()];

	thresh_img(bitmap_A2, bitmap_A2_arr, threshVal_A2);
	thresh_img(bitmap_GT, bitmap_GT_arr, threshVal_GT);

	readDoubleCSV("alg_dbl.csv", cont_res_ptr);

	// open PR_img.csv file
	std::ofstream pr_img_csv_file;
	pr_img_csv_file.open("PR_img");

	// fill in thresholdValues array with values 25:250, increment:25
	for (int index = 1; index <= threshold_val_len; index++)
	{
		thresholdValues[index] = (double)index * 25;
	}

	try
	{
		for (int juggernaut = 0; juggernaut < threshold_val_len; juggernaut++)
		{
			// thresh_v(cont_res_ptr, bitmap_A2_arr, csv_len, thresholdValues[juggernaut]);
			if (calcPR(bitmap_A2_arr, bitmap_GT_arr, 125, &P, &R))
			{
				double FB = calcFb(P, R, 1);
				std::cout << P << "," << R << std::endl;
				if (FB > F1)
				{
					F1 = FB;
					selectThresh = thresholdValues[juggernaut];
				}
			}
		}
	}
	catch (...)
	{
		std::cout << "Part IV: max F1 = " << F1 << " at max threshold = " << threshVal_A2 << std::endl;
	}

	std::cout << "Part IV: max F1 = " << F1 << " at max threshold = " << selectThresh << std::endl;

	delete[] bitmap_A2_arr;
	delete[] bitmap_GT_arr;
	delete[] cont_res_ptr;
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
			break;
		case 2:
			option_2();
			break;
		case 3:
			option_3();
			break;
		case 4:
			option_4();
			break;
		case 5:
			std::cout << "exiting program" << std::endl;
			exit(0);
		default:
			std::cout << "You have entered an incorrect option...\n";
			break;
		}

		fflush(stdin);
	}

	return 0;
}
