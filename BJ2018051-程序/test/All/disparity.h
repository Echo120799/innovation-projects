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

	enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3, STEREO_3WAY = 4 };//ö��

	//Mat img1 = imread("C:\\Users\\lenovo\\Desktop\\left.jpg", IMREAD_GRAYSCALE);
	//Mat img2 = imread("C:\\Users\\lenovo\\Desktop\\right.jpg", IMREAD_GRAYSCALE);
	namedWindow("left", 1);
	imshow("left", img1);
	namedWindow("right", 1);
	imshow("right", img2);

	int cn = img1.channels();
	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);//mindisparity, ndisparities, SADWindowSize
	sgbm->setPreFilterCap(63);
	int SADWindowSize = 9;//s����
	int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
	int numberOfDisparities = 64;//d����
	sgbm->setBlockSize(sgbmWinSize);
	sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setMinDisparity(0);//��С�Ӳ�
	sgbm->setNumDisparities(numberOfDisparities);//�Ӳ�ڣ�������Ӳ�ֵ����С�Ӳ�ֵ֮��
	sgbm->setUniquenessRatio(3);//uniquenessRatio��Ҫ���Է�ֹ��ƥ��,ʹ��ƥ�书��ģʽ��r����
	sgbm->setSpeckleWindowSize(100); //����Ӳ���ͨ����仯�ȵĴ��ڴ�С, ֵΪ0ʱȡ�� speckle ���
	sgbm->setSpeckleRange(32);// �Ӳ�仯��ֵ�����������Ӳ�仯������ֵʱ���ô����ڵ��Ӳ�����
	sgbm->setDisp12MaxDiff(1);//���Ӳ�ͼ��ֱ�Ӽ���ó��������Ӳ�ͼ��ͨ��cvValidateDisparity����ó���֮������������죬Ĭ��Ϊ-1


	Mat disp, disp8;
	int alg = STEREO_SGBM;
	if (alg == STEREO_HH)
		sgbm->setMode(cv::StereoSGBM::MODE_HH);
	else if (alg == STEREO_SGBM)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM);
	else if (alg == STEREO_3WAY)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
	sgbm->compute(img1, img2, disp);

	disp.convertTo(disp8, CV_8U, 255 / (numberOfDisparities*16.));//��������Ӳ���CV_16S��ʽ

	namedWindow("disparity", 1);
	imshow("disparity", disp8);
	waitKey();
	imwrite("SGBM_disparity.jpg", disp8);
	//cvDestroyAllWindows();
	return disp8;
}