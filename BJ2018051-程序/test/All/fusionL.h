#pragma once
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace cv;
using namespace std;


void fusionL(Mat background, Mat foreground, Mat disparityMap, Mat output, Point2i location, int disparity)//背景图，目标图，视差图，输出结果图，插入位置,视差值
{

	background.copyTo(output);
	int y;
	int x;
	for (y = location.y; y < background.rows; ++y)
	{
		int fY = y - location.y;
		if (fY >= foreground.rows)//插入物体y范围
			break;

		for (x = location.x; x < background.cols; ++x)
		{
			int fX = x - location.x;
			if (fX >= foreground.cols)//插入物体x范围
				break;

			// gray_newmask.ptr<uchar>(i)[j]
			double opacity = ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.0;


			// and now combine the background and foreground pixel, using the opacity,

			// but only if opacity > 0.
			for (int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx =
					foreground.data[fY * foreground.step + fX * foreground.channels() + c];
				unsigned char backgroundPx =
					background.data[y * background.step + x * background.channels() + c];

				if (disparityMap.data[y * disparityMap.step + x * disparityMap.channels()] < disparity)
				{
					output.data[y*output.step + output.channels()*x + c] = foregroundPx;
				}
			}
		}
	}
	imshow("outputL", output);
	imwrite("outputL.jpg", output);
	waitKey(0);
	return;
}