#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>



#include"disparity.h"
#include"kmeans.h"
//#include"grabcut.h"
#include"kmeans_disparity.h"
#include"filter.h"
#include"fusionL.h"
#include"fusionR.h"


using namespace cv;
using namespace std;

int main()
{
	Mat image_L = imread("left1.png");
	Mat image_R = imread("right1.png");
	Mat img_sgm = imread("sgm1.jpg");
	Mat grabcut = imread("grabcut1.jpg");
	Mat img_sgm_gray;
	cvtColor(img_sgm, img_sgm_gray, CV_RGB2GRAY);

	Mat img_disparity = disparity(image_L, image_R);//SGBM
	//Mat img_kmeans_L= kmeans(image_L);
	//Mat img_kmeans_disparity_L = kmeans_disparity(img_kmeans_L, img_sgm_gray);
	Mat img_kmeans_disparity_L = kmeans_disparity(grabcut, img_sgm_gray);
	//Mat img_filter_L= filter(img_kmeans_disparity_L);
	Mat img_filter_L = filter(img_kmeans_disparity_L);



	Mat object = imread("D:\\pictures\\000002.png", -1);

	Mat object_scale;	//目标图进行缩放
	float scale = 0.4;	//缩放比例
	resize(object, object_scale, Size(0, 0), scale, scale);

	Mat output_L;//左视图结果图
	Mat output_R;//左视图结果图
	int disparity = 71;
	int dis = 40;
	fusionL(image_L, object_scale, img_filter_L, output_L, Point(260, 150), disparity);
	fusionR(image_R, object_scale, img_filter_L, output_R, Point(260 - dis, 150), disparity, dis);

}