// watermark-remover.cpp : Defines the entry point for the console application.
// Developed based on morsphology tutorial from the opencv website.
// Pass in an argument of your image path through windows command line and run.
// Use trackbar to remove watermarks until satisfaction, result automatically
// stores in the same path as original image.
// Url: https://docs.opencv.org/master/d3/dbe/tutorial_opening_closing_hats.html
// Author: Wei Guo wei.parker.guo@gmail.com

#include "stdafx.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

Mat src, dst;
String src_name;
int morph_elem = 0;
int morph_size = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;
const char* window_name = "Morphology Transformations Demo";

//function declare
void Morphology_Operations(int, void*);

int main(int argc, char** argv)
{
	CommandLineParser parser(argc, argv, "{@input | ../data/baboon.jpg | input image}");
	src_name = parser.get<String>("@input");
	src = imread(src_name, IMREAD_COLOR);
	if (src.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	namedWindow(window_name, WINDOW_AUTOSIZE); // Create window
	createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
		&morph_elem, max_elem,
		Morphology_Operations);
	createTrackbar("Kernel size:\n 2n +1", window_name,
		&morph_size, max_kernel_size,
		Morphology_Operations);
	Morphology_Operations(0, 0);
	waitKey(0);
	return 0;
}
void Morphology_Operations(int, void*)
{
	// Use MORPH_X 2 for opening morphology
	Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, dst, 2, element);

	imshow(window_name, dst);
	imwrite(src_name + "_removed.jpg", dst);
}