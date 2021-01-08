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
	//���������������Ϊ��GC_BGD =0��������,GC_FGD =1��ǰ����,GC_PR_BGD = 2�����ܵı�����, GC_PR_FGD = 3�����ܵ�ǰ����		
	Mat result = Mat::zeros(src.size(), CV_8UC1);
	// GrabCut ��ͼ
	//������ʱ�����������Ϊ�㷨���м����ʹ��
	Mat bgModel, fgModel;
	char c = waitKey(0);
	if (c == 'g') {
		grabCut(src, result, rect, bgModel, fgModel, 1, GC_INIT_WITH_RECT);
		//�Ƚ�result��ֵΪ���ܵ�ǰ�����ز������result��
		compare(result, GC_PR_FGD, result, CMP_EQ);
		// �������ͼ��
		Mat foreground(src.size(), CV_8UC3, Scalar(0, 0, 0));
		//��ԭͼ��src�е�result���򿽱���foreground��
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
//���ѡ����ο�
void onMouse(int event, int x, int y, int flags, void* userdata) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN://�����������¼�
		rect.x = x;
		rect.y = y;
		rect.width = 1;
		rect.height = 1;
		break;
	case CV_EVENT_MOUSEMOVE://����ƶ��¼�
		if (flags && CV_EVENT_FLAG_LBUTTON) {
			rect = Rect(Point(rect.x, rect.y), Point(x, y));
			showImg();
		}
		break;
	case EVENT_LBUTTONUP://��굯���¼�
		if (rect.width > 1 && rect.height > 1) {
			showImg();
		}
		break;
	default:
		break;
	}
}





