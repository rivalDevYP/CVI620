/**************************************************************************************
//
//   We, Yathavan Parameshwaran, Gabriella Ko, and Patrick O'Reilly, declare that the attached assignment
//   is our own work in accordance with the Seneca Academic Policy.
//   We have not copied any part of this assignment, manually or electronically,
//   from any other source including web sites, unless specified as references.
//   We have not distributed our work to other students.
//
**************************************************************************************/

// Example 9-2. Toy program for using a mouse to draw boxes on the screen
#include <opencv2/opencv.hpp>

using namespace cv;

// ADDED: LAB4 storing colour choice, white as default
cv::Scalar selectedColour = cv::Vec3b(255, 255, 255);
// ADDED: LAB4 pt2.3.d/e/f storing flag for temp shape none to start
int flagHolder{ 0 };

// Define our callback which we will install for
// mouse events
//
void my_mouse_callback(

	int event, int x, int y, int flags, void* param
);
cv::Rect box;
bool drawing_box = false;


// A little subroutine to draw a box onto an image
//
void draw_box(cv::Mat& img, cv::Rect box, int shape = 0) {
	// ADDED: LAB4 pt 2.3.d calculate and store radius for circle
	int rad = cv::abs(box.height) < cv::abs(box.width) ? box.height/2 : box.width/2;
	// ADDED: LAB4 pt.2.3.e calculate and store axes for ellipse
	cv::Size axes = cv::Size(cv::abs(box.width/2), cv::abs(box.height/2));

	switch (shape)
	{
	case cv::EVENT_FLAG_SHIFTKEY:
		cv::circle(
			img,
			// centre of rectangle
			cv::Point(box.tl().x + box.width / 2, box.tl().y + box.height / 2),
			// radius
			cv::abs(rad),
			selectedColour,
			2
		);
		break;
	case cv::EVENT_FLAG_CTRLKEY:
		cv::ellipse(
			img,
			// centre of ellipse
			cv::Point(box.tl().x + (box.width / 2), box.tl().y + (box.height / 2)), // centre of rectangle
			axes,
			// angles
			0,0,360,
			selectedColour,
			2
		);
		break;
	default:
		cv::rectangle(
			img,
			box.tl(),
			box.br(),
			selectedColour,
			// ADDED: LAB4 pt2.7.f thickness to 2
			2
		);
		break;
	}


}
void help(char** argv) {
	std::cout << "Example 9-2. Toy program for using a mouse to draw boxes on the screen"
		<< "\nCall:\n" << argv[0] <<
		"\n\nshows how to use a mouse to draw regions in an image. Esc to quit\n" << std::endl;
}
int main(int argc, char** argv) {
	help(argv);
	box = cv::Rect(-1, -1, 0, 0);
	// ADDED: LAB4 pt2.7.a changed size
	cv::Mat image(480, 640, CV_8UC3), temp;
	image.copyTo(temp);
	box = cv::Rect(-1, -1, 0, 0);
	image = cv::Scalar::all(0);
	cv::namedWindow("Box Example");
	// ADDED: LAB4 pt2.7.b move window
	cv::moveWindow("Box Example", 10, 30);
	// Here is the crucial moment where we actually install
	// the callback. Note that we set the value of 'params' to
	// be the image we are working with so that the callback
	// will have the image to edit.
	//
	cv::setMouseCallback(
		"Box Example",
		my_mouse_callback,
		(void*)&image
	);

	// ADDED: LAB4 pt2.7.h for text
	cv::String text = "My Drawing Application";
	int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;
	// center the text
	Point textOrg((image.cols - textSize.width) / 2,
		40);
	// ... and the baseline first
	line(image, textOrg + Point(0, thickness),
		textOrg + Point(textSize.width, thickness),
		Scalar(0, 0, 255));
	// then put the text itself
	putText(image, text, textOrg, fontFace, fontScale,
		Scalar::all(255), thickness, 8);

	// The main program loop. Here we copy the working image
	// to the temp image, and if the user is drawing, then
	// put the currently contemplated box onto that temp image.
	// Display the temp image, and wait 15ms for a keystroke,
	// then repeat.
	//
	for (;;) {
		// ADDED: LAB4 pt2.7.c colour selection and exit control
		int control = cv::waitKey(15);
		// setting the color choice
		switch (control)
		{
		case 107: // k for black
			selectedColour = cv::Vec3b(0, 0, 0);
			break;
		case 119: // w for white
			selectedColour = cv::Vec3b(255, 255, 255);
			break;
		case 114: // r for red
			selectedColour = cv::Vec3b(0, 0, 255);
			break;
		case 103: // g for green
			selectedColour = cv::Vec3b(0, 255, 0);
			break;
		case 98: // b for blue
			selectedColour = cv::Vec3b(255, 0, 0);
			break;
		case 99: // c for cyan
			selectedColour = cv::Vec3b(255, 255, 0);
			break;
		case 121: // y for yellow
			selectedColour = cv::Vec3b(0, 255, 255);
			break;
		case 109: // m for magenta
			selectedColour = cv::Vec3b(255, 0, 255);
			break;
		case 120: // x for random
			selectedColour = cv::Vec3b(rand() % 256, rand() % 256, rand() % 256);
			break;
		};
		image.copyTo(temp);
		if (drawing_box) draw_box(temp, box, flagHolder);
		cv::imshow("Box Example", temp);
		if (control == 27) {
			// ADDED: LAB4 pt2.3.g close window and ask to save, only saves one image, overwrites image
			char save;
			destroyWindow("Box Example");
			std::cout << "Would you like to save your masterpiece?(y/n): ";
			std::cin >> save;
			if (save == 'y')
			{
				cv::imwrite("masterpiece.jpeg", image);
			}
			break;
		}
	}
	return 0;
}

// This is our mouse callback. If the user
// presses the left button, we start a box.
// When the user releases that button, then we
// add the box to the current image. When the
// mouse is dragged (with the button down) we
// resize the box.
//
void my_mouse_callback(
	int event, int x, int y, int flags, void* param)
{
	// set flagholder to display desired shape as mouse is drawing
	if (flags & cv::EVENT_FLAG_SHIFTKEY)
	{
		flagHolder = cv::EVENT_FLAG_SHIFTKEY;
	}
	else if (flags & cv::EVENT_FLAG_CTRLKEY)
	{
		flagHolder = cv::EVENT_FLAG_CTRLKEY;
	}
	else
	{
		flagHolder = 0;
	}
	cv::Mat& image = *(cv::Mat*) param;
	switch (event) {
	case cv::EVENT_MOUSEMOVE: {
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
	}
							break;
	case cv::EVENT_LBUTTONDOWN: {
		drawing_box = true;
		box = cv::Rect(x, y, 0, 0);
	}
							  break;
	case cv::EVENT_LBUTTONUP: {
		drawing_box = false;
		if (box.width < 0) {

			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0) {
			box.y += box.height;
			box.height *= -1;
		}
		draw_box(image, box, flags);
	}
							break;
	}

}
