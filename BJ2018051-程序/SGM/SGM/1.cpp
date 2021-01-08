#include "stdafx.h"
#include "SemiGlobalMatching.h"

// opencv
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main()
{
	Mat img_left = imread("left3.png", IMREAD_GRAYSCALE);
	Mat img_right = imread("right3.png", IMREAD_GRAYSCALE);
	

	const uint32 width = static_cast<uint32>(img_left.cols);
	const uint32 height = static_cast<uint32>(img_right.rows);

	SemiGlobalMatching::SGMOption sgm_option;
	sgm_option.num_paths = 8;
	sgm_option.min_disparity = 0;
	sgm_option.max_disparity = 128;
	sgm_option.p1 = 10;
	sgm_option.p2_init = 1500;

	SemiGlobalMatching sgm;

	// ≥ı ºªØ
	if (!sgm.Initialize(width, height, sgm_option)) {
		std::cout << "SGM≥ı ºªØ ß∞‹£°" << std::endl;
		return -2;
	}

	// ∆•≈‰
	auto disparity = new float32[width * height]();
	if (!sgm.Match(img_left.data, img_right.data, disparity)) {
		std::cout << "SGM∆•≈‰ ß∞‹£°" << std::endl;
		return -2;
	}

	// œ‘ æ ”≤ÓÕº
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

	namedWindow(" ”≤ÓÕº");
	imshow(" ”≤ÓÕº", disp_mat);
	imwrite("sgm3.jpg", disp_mat);

	namedWindow("left");
	imshow("left", img_left);
	waitKey(0);

	return 0;
}