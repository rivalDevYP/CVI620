// Example 2-10. The same object can load videos from a camera or a file
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <dirent.h>

void help(char **argv)
{
	std::cout << "\n"
			  << "\nxample 2-10. The same object can load videos from a camera or a file"
			  << "\nCall:\n"
			  << argv[0] << " [path/image]\n"
			  << "\nor, read from camera:\n"
			  << argv[0]
			  << "\nFor example:\n"
			  << argv[0] << " ../tree.avi\n"
			  << std::endl;
}

int getNumJPG()
{
	DIR *currentDir = NULL;
	currentDir = opendir(".");
	struct dirent *de_1 = NULL;

	size_t num = 0;

	while ((de_1 = readdir(currentDir)) != NULL)
	{
		std::string fileName(de_1->d_name);
		if (fileName.find('.') != std::string::npos)
		{
			if (fileName.substr(fileName.find('.'), fileName.length()) == ".jpg")
			{
				num++;
			}
		}
	}
	return num;
}

int main(int argc, char **argv)
{

	help(argv);

	char buffer[32];

	cv::namedWindow("Example 2-10", cv::WINDOW_AUTOSIZE);
	cv::VideoCapture cap;

	if (argc == 1)
	{
		cap.open(0); // open the first camera
	}
	else
	{
		cap.open(argv[1]);
	}

	if (!cap.isOpened())
	{ // check if we succeeded
		std::cerr << "Couldn't open capture." << std::endl;
		return -1;
	}

	cv::Mat frame;

	// output width and height of video captured
	std::cout << "Width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
	std::cout << "Height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;

	for (;;)
	{

		cap >> frame;

		if (frame.empty())
			break; // Ran out of film

		cv::imshow("Example 2-10", frame);

		// picture if x is pressed, exit if enter is pressed
		char keyPressed = (char)cv::waitKey(33);
		if (keyPressed == 120)
		{
			cv::waitKey(1000);
			sprintf(buffer, "image%02d.jpg", getNumJPG());
			cv::imwrite(buffer, frame);
		}
		else if (keyPressed == 32 || keyPressed == 13)
		{
			return 0;
		}
	}

	return 0;
}