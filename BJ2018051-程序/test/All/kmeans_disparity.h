#pragma once
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
using namespace cv;
using namespace std;

Mat kmeans_disparity(Mat kmeans,Mat disparityImg)
{
	Mat result = Mat::zeros(disparityImg.size(), disparityImg.type());
	Mat kmeans_gray;
	int disparity = 72;
	cvtColor(kmeans, kmeans_gray, CV_RGB2GRAY);
	imshow("1", kmeans_gray);
	
	
	for (int i = 0; i < kmeans.rows; i++)
	{
		for (int j = 0; j < kmeans.cols; j++)
			if (kmeans_gray.ptr<uchar>(i)[j] > 200 &&disparityImg.ptr<uchar>(i)[j] > disparity)
			{
	            result.ptr<uchar>(i)[j] = kmeans_gray.ptr<uchar>(i)[j];
			}

			else result.ptr<uchar>(i)[j] = 0;

	}
	imshow("kmeans_disparity", result);
	imwrite("grabcut_disparity.jpg", result);
	waitKey(0);
	return result;
}
