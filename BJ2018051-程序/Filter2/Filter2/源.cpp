#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "extract.h"

using namespace cv;
using namespace std;

int main()
{
	Mat img = imread("left3.png");
	Mat sgm = imread("sgm3.jpg");
	Mat mask(sgm.rows, sgm.cols, CV_8U, Scalar(0));
	int disparity = 60;

	extract(sgm, mask, disparity);

	namedWindow("before", CV_WINDOW_AUTOSIZE);
	imshow("before", mask);

	//形态学处理
	Mat element = getStructuringElement(MORPH_ELLIPSE, Size(4, 4));
	erode(mask, mask, element);//腐蚀
	dilate(mask, mask, element);//膨胀
	medianBlur(mask, mask, 5);

	Mat result;
	img.copyTo(result, mask);

	namedWindow("mask", CV_WINDOW_AUTOSIZE);
	imshow("mask", mask);
	imwrite("mask3_2.jpg", mask);

	namedWindow("result", CV_WINDOW_AUTOSIZE);
	imshow("result", result);

	waitKey(0);

	return 0;
}
