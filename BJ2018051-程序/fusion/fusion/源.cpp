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

	// 遍历背景图片矩阵--------------------
	//行循环rows
	for (int y = max(location.y, 0); y < background.rows; ++y)
	{
		int fY = y - location.y; // fy移动插入图片之后的新坐标
		//当行数大于插入照片时 停止
		if (fY >= foreground.rows)
			break;

		// 列循环cols
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
	//实景照片导入--------------
	Mat sourceImgL,disparityImg1,disparityImg2;
	sourceImgL = imread("left1.png");
	disparityImg1 = imread("mask1_1.jpg");
	disparityImg2 = imread("mask1_2.jpg");

	if (!sourceImgL.data) //如果没读出图片
	{
		printf("NO IMAGE DATA!");
		return -1;
	}

	//处理并显示视频-------------
	Mat frame, resizedFrame;
	Mat resultImgL;
	float scale = 0.5; //用于resize插入图片
	namedWindow("vedio");
	imshow("vedio", sourceImgL);
	

	int delat = 1000 / 25; //每帧之间d延迟时间

	int num = 999;
	char fileName[50];
	int disparity;
	char c = waitKey(0);;
		if(c == 'w')
		{
			disparity = 73;
			for (int i = 1; i < num; i++)
			{
				//循环导入插入图片 4通道格式
				sprintf_s(fileName, "D:/pictures/鸟/00%03d.png", i);
				frame = imread(fileName, -1);
				if (frame.data)//如果有数据就执行叠加，如果没有就结束
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
				//循环导入插入图片 4通道格式
				sprintf_s(fileName, "D:/pictures/鸟/00%03d.png", i);
				frame = imread(fileName, -1);
				if (frame.data)//如果有数据就执行叠加，如果没有就结束
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
		//循环导入插入图片 4通道格式
		sprintf_s(fileName, "D:/pictures/鸟/00%03d.png", i);
		frame = imread(fileName, -1);
		if (frame.data)//如果有数据就执行叠加，如果没有就结束
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

		waitKey(delat);//要有这句，才会输出视频
   //在显示每一帧都采用了延时方法。延时的时长取决于视频的帧频率（fps为帧速率，1000/fps为两帧之间的毫秒数）
	   //通过修改delat的值，可以使视频快进或慢进
	   //将delat设置为0，按照用户按键，才播放。
	}*/
	return 0;
	

}

