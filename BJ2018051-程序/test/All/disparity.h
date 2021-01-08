#pragma once
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

Mat disparity(Mat img1,Mat img2)
{

	enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3, STEREO_3WAY = 4 };//枚举

	//Mat img1 = imread("C:\\Users\\lenovo\\Desktop\\left.jpg", IMREAD_GRAYSCALE);
	//Mat img2 = imread("C:\\Users\\lenovo\\Desktop\\right.jpg", IMREAD_GRAYSCALE);
	namedWindow("left", 1);
	imshow("left", img1);
	namedWindow("right", 1);
	imshow("right", img2);

	int cn = img1.channels();
	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);//mindisparity, ndisparities, SADWindowSize
	sgbm->setPreFilterCap(63);
	int SADWindowSize = 9;//s参数
	int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
	int numberOfDisparities = 64;//d参数
	sgbm->setBlockSize(sgbmWinSize);
	sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setMinDisparity(0);//最小视差
	sgbm->setNumDisparities(numberOfDisparities);//视差窗口，即最大视差值与最小视差值之差
	sgbm->setUniquenessRatio(3);//uniquenessRatio主要可以防止误匹配,使用匹配功能模式，r参数
	sgbm->setSpeckleWindowSize(100); //检查视差连通区域变化度的窗口大小, 值为0时取消 speckle 检查
	sgbm->setSpeckleRange(32);// 视差变化阈值，当窗口内视差变化大于阈值时，该窗口内的视差清零
	sgbm->setDisp12MaxDiff(1);//左视差图（直接计算得出）和右视差图（通过cvValidateDisparity计算得出）之间的最大容许差异，默认为-1


	Mat disp, disp8;
	int alg = STEREO_SGBM;
	if (alg == STEREO_HH)
		sgbm->setMode(cv::StereoSGBM::MODE_HH);
	else if (alg == STEREO_SGBM)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM);
	else if (alg == STEREO_3WAY)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
	sgbm->compute(img1, img2, disp);

	disp.convertTo(disp8, CV_8U, 255 / (numberOfDisparities*16.));//计算出的视差是CV_16S格式

	namedWindow("disparity", 1);
	imshow("disparity", disp8);
	waitKey();
	imwrite("SGBM_disparity.jpg", disp8);
	//cvDestroyAllWindows();
	return disp8;
}