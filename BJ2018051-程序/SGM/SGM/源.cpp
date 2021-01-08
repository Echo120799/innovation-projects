/* -*-c++-*- SemiGlobalMatching - Copyright (C) 2020.
* Author	: Ethan Li <ethan.li.whu@gmail.com>
* Describe	: main
*/

#include "stdafx.h"
#include "SemiGlobalMatching.h"

// opencv
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib,"opencv_world411d.lib")
#else
#pragma comment(lib,"opencv_world411.lib")
#endif


/**
 * \brief
 * \param argv 3
 * \param argc argc[1]:��Ӱ��·�� argc[2]: ��Ӱ��·�� argc[3]: �Ӳ�ͼ·��
 * \return
 */
int main(int argv, char** argc)
{
	if (argv < 3) {
		return 0;
	}

	// ������ ��ȡӰ��
	std::string path_left = "";
	std::string path_right = argc[2];

	cv::Mat img_left = cv::imread(path_left, cv::IMREAD_GRAYSCALE);
	cv::Mat img_right = cv::imread(path_right, cv::IMREAD_GRAYSCALE);

	if (img_left.data == nullptr || img_right.data == nullptr) {
		std::cout << "��ȡӰ��ʧ�ܣ�" << std::endl;
		return -1;
	}
	if (img_left.rows != img_right.rows || img_left.cols != img_right.cols) {
		std::cout << "����Ӱ��ߴ粻һ�£�" << std::endl;
		return -1;
	}

	// SGMƥ��
	const uint32 width = static_cast<uint32>(img_left.cols);
	const uint32 height = static_cast<uint32>(img_right.rows);

	SemiGlobalMatching::SGMOption sgm_option;
	sgm_option.num_paths = 8;
	sgm_option.min_disparity = 0;
	sgm_option.max_disparity = 64;
	sgm_option.p1 = 10;
	sgm_option.p2_init = 1500;

	SemiGlobalMatching sgm;

	// ��ʼ��
	if (!sgm.Initialize(width, height, sgm_option)) {
		std::cout << "SGM��ʼ��ʧ�ܣ�" << std::endl;
		return -2;
	}

	// ƥ��
	auto disparity = new float32[width * height]();
	if (!sgm.Match(img_left.data, img_right.data, disparity)) {
		std::cout << "SGMƥ��ʧ�ܣ�" << std::endl;
		return -2;
	}

	// ��ʾ�Ӳ�ͼ
	cv::Mat disp_mat = cv::Mat(height, width, CV_8UC1);
	for (uint32 i = 0; i < height; i++) {
		for (uint32 j = 0; j < width; j++) {
			const float32 disp = disparity[i * width + j];
			if (disp == Invalid_Float) {
				disp_mat.data[i * width + j] = 0;
			}
			else {
				disp_mat.data[i * width + j] = 2 * static_cast<uchar>(disp);
			}
		}
	}
	cv::imwrite(argc[3], disp_mat);
	cv::imshow("�Ӳ�ͼ", disp_mat);
	cv::waitKey(0);

	delete[] disparity;
	disparity = nullptr;

	return 0;
}
