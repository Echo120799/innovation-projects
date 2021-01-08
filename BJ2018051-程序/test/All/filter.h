#pragma once
#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

Mat filter(Mat img)
{
	Mat out;
	/*int g_nStructElementSize = 8; //结构元素(内核矩阵)的尺寸
	Mat element = getStructuringElement(MORPH_RECT, Size(g_nStructElementSize, g_nStructElementSize));
	morphologyEx(img, out, MORPH_CLOSE, element);*/

	Mat img1;
	Mat img2;
	Point anchor = Point(-1, -1);
	int iterations = 1;
	int borderType = BORDER_CONSTANT;
	const Scalar& borderValue = morphologyDefaultBorderValue();
	dilate(img, img1, Mat(3, 3, CV_8UC1), anchor, iterations, borderType, borderValue);
	erode(img1, img2, Mat(3, 3, CV_8UC1), anchor, iterations, borderType, borderValue);//腐蚀
	//dilate(img1, img2, Mat(3, 3, CV_8UC1), anchor, iterations, borderType, borderValue);
	medianBlur(img2, out, 3);

	namedWindow("形态学处理操作");
	imshow("形态学处理操作", out);
	imwrite("filter.jpg", out);
	waitKey(0);
	return(out);
}