#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>


using namespace cv;
void onMouse(int event, int x, int y, int flags, void* userdata);
Rect rect;
Mat src, roiImg, result;
void showImg();
int main() 
{
	src = imread("left3.jpg");
	namedWindow("input", CV_WINDOW_AUTOSIZE);
	imshow("input", src);
	setMouseCallback("input", onMouse);
	//定义输出结果，结果为：GC_BGD =0（背景）,GC_FGD =1（前景）,GC_PR_BGD = 2（可能的背景）, GC_PR_FGD = 3（可能的前景）		
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	// GrabCut 抠图
	//两个临时矩阵变量，作为算法的中间变量使用
	Mat bgModel, fgModel;
	char c = waitKey(0);
	if (c == 'g') {
		grabCut(src, result, rect, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
		//比较result的值为可能的前景像素才输出到result中
		compare(result, GC_PR_FGD, result, CMP_EQ);
		// 产生输出图像
		Mat foreground(src.size(), CV_8UC3, Scalar(0, 0, 0));
		//将原图像src中的result区域拷贝到foreground中
		src.copyTo(foreground, result);
		imshow("output", foreground);
		//imwrite("grabcut3.jpg", foreground);
		imwrite("grabcut3_color.jpg", foreground);
		imwrite("grabcut3.jpg", result);
		
	}
	waitKey(0);
	return 0;
}


void showImg() {
	src.copyTo(roiImg);
	rectangle(roiImg, rect, Scalar(0, 0, 255), 2);
	imshow("input", roiImg);
}
//鼠标选择矩形框
void onMouse(int event, int x, int y, int flags, void* userdata) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://鼠标左键按下事件
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE://鼠标移动事件
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP://鼠标弹起事件
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}





