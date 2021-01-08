#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>


using namespace std;
using namespace cv;

void virtualRealityFusion(const Mat &background, const Mat &foreground, const Mat &disparityMap,
	Mat &output, Point2i location, int disparity)
{
	background.copyTo(output);

	// ��������ͼƬ����--------------------
	//��ѭ��rows
	for (int y = max(location.y, 0); y < background.rows; ++y)
	{
		int fY = y - location.y; // fy�ƶ�����ͼƬ֮���������
		//���������ڲ�����Ƭʱ ֹͣ
		if (fY >= foreground.rows)
			break;

		// ��ѭ��cols
		for (int x = max(location.x, 0); x < background.cols; ++x)
		{
			int fX = x - location.x; // because of the translation.
			if (fX >= foreground.cols)
				break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity =
				((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.;


			// and now combine the background and foreground pixel, using the opacity,

			// but only if opacity > 0.
			for (int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					foreground.data[fY * foreground.step + fX * foreground.channels() + c];
				unsigned char backgroundPx =
					background.data[y * background.step + x * background.channels() + c];

				if (disparityMap.data[y * disparityMap.step + x * disparityMap.channels()] > disparity)
				{
					output.data[y*output.step + output.channels()*x + c] =
						backgroundPx;
				}
				else
				{
					output.data[y*output.step + output.channels()*x + c] =
						backgroundPx * (1. - opacity) + foregroundPx * opacity;
				}
			}
		}
	}
}


int main(int argc, char** argv)
{
	//ʵ����Ƭ����--------------
	Mat sourceImgL,disparityImg1,disparityImg2;
	sourceImgL = imread("left1.png");
	disparityImg1 = imread("mask1_1.jpg");
	disparityImg2 = imread("mask1_2.jpg");

	if (!sourceImgL.data) //���û����ͼƬ
	{
		printf("NO IMAGE DATA!");
		return -1;
	}

	//������ʾ��Ƶ-------------
	Mat frame, resizedFrame;
	Mat resultImgL;
	float scale = 0.5; //����resize����ͼƬ
	namedWindow("vedio");
	imshow("vedio", sourceImgL);
	

	int delat = 1000 / 25; //ÿ֮֡��d�ӳ�ʱ��

	int num = 999;
	char fileName[50];
	int disparity;
	char c = waitKey(0);;
		if(c == 'w')
		{
			disparity = 73;
			for (int i = 1; i < num; i++)
			{
				//ѭ���������ͼƬ 4ͨ����ʽ
				sprintf_s(fileName, "D:/pictures/��/00%03d.png", i);
				frame = imread(fileName, -1);
				if (frame.data)//��������ݾ�ִ�е��ӣ����û�оͽ���
				{
					resize(frame, resizedFrame, Size(0, 0), scale, scale);
					//namedWindow("origin");
					//imshow("origin", resizedFrame);
					virtualRealityFusion(sourceImgL, resizedFrame, disparityImg1, resultImgL, cv::Point(220, 120), disparity);
					imshow("vedio", resultImgL);

				}
				else
				{
					break;
				}

				waitKey(delat);
			}
			
		}
		if (c == 's')
		{
			disparity = 55;
			for (int i = 1; i < num; i++)
			{
				//ѭ���������ͼƬ 4ͨ����ʽ
				sprintf_s(fileName, "D:/pictures/��/00%03d.png", i);
				frame = imread(fileName, -1);
				if (frame.data)//��������ݾ�ִ�е��ӣ����û�оͽ���
				{
					resize(frame, resizedFrame, Size(0, 0), scale, scale);
					//imshow("origin", resizedFrame);
					virtualRealityFusion(sourceImgL, resizedFrame, disparityImg2, resultImgL, cv::Point(200, 0), disparity);
					imshow("vedio", resultImgL);

				}
				else
				{
					break;
				}

				waitKey(delat);

			}
		}
	/*for (int i = 1; i < num; i++)
	{
		//ѭ���������ͼƬ 4ͨ����ʽ
		sprintf_s(fileName, "D:/pictures/��/00%03d.png", i);
		frame = imread(fileName, -1);
		if (frame.data)//��������ݾ�ִ�е��ӣ����û�оͽ���
		{
			resize(frame, resizedFrame, Size(0, 0), scale, scale);
			imshow("origin", resizedFrame);
			virtualRealityFusion(sourceImgL, resizedFrame, disparityImg1, resultImgL, cv::Point(200, 0), disparity);
			imshow("vedio", resultImgL);

		}
		else
		{
			break;
		}

		waitKey(delat);//Ҫ����䣬�Ż������Ƶ
   //����ʾÿһ֡����������ʱ��������ʱ��ʱ��ȡ������Ƶ��֡Ƶ�ʣ�fpsΪ֡���ʣ�1000/fpsΪ��֮֡��ĺ�������
	   //ͨ���޸�delat��ֵ������ʹ��Ƶ���������
	   //��delat����Ϊ0�������û��������Ų��š�
	}*/
	return 0;
	

}

