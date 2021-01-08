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

Mat kmeans(Mat img1)
{
	Mat src = img1;
	if (src.empty())
	{
		printf("read image error\n");
		system("pause");
		
	}

	//imshow("src", src);

	Scalar colorTab[] = {
	 Scalar(0, 255, 255),
	 Scalar(255, 0, 0),
	 Scalar(0, 0, 255),
	 Scalar(255, 0, 255),
	 Scalar(255, 255, 255)
	};

	int width = src.cols;
	int height = src.rows;
	int dims = src.channels();

	// 初始化定义
	int sampleCount = width * height;
	int clusterCount = 5;
	Mat points(sampleCount, dims, CV_32F, Scalar(10));
	Mat labels;
	Mat centers(clusterCount, 1, points.type());

	// RGB 数据类型转化到样本数据
	int index = 0;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			// 多维转一维
			index = row * width + col;
			Vec3b bgr = src.at<Vec3b>(row, col);
			points.at<float>(index, 0) = static_cast<int>(bgr[0]);
			points.at<float>(index, 1) = static_cast<int>(bgr[1]);
			points.at<float>(index, 2) = static_cast<int>(bgr[2]);
		}
	}

	// KMeans
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1);
	kmeans(points, clusterCount, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

	// 显示图像分割后的结果，一维转多维
	Mat result = Mat::zeros(src.size(), src.type());
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			index = row * width + col;
			int label = labels.at<int>(index, 0);
			result.at<Vec3b>(row, col)[0] = colorTab[label][0];
			result.at<Vec3b>(row, col)[1] = colorTab[label][1];
			result.at<Vec3b>(row, col)[2] = colorTab[label][2];
		}
	}

	imshow("kmeans", result);
	imwrite("kmeans.jpg", result);
	waitKey(0);
	return(result);

}