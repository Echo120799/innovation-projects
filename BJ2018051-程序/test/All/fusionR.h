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


void fusionR(Mat background, Mat foreground, Mat disparityMap, Mat output, Point2i location, int disparity, int dis)//背景图，目标图，视差图，输出结果图，插入位置,视差值
{


	background.copyTo(output);
	for (int y = location.y; y < background.rows; y++)
	{
		int fY = y - location.y;

		if (fY >= foreground.rows)
			break;


		for (int x = location.x; x < background.cols; x++)
		{
			int fX = x - location.x;
			if (fX >= foreground.cols)
				break;

			// determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
			double opacity = ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3]) / 255.;


			for (int c = 0; opacity > 0 && c < output.channels(); ++c)
			{
				unsigned char foregroundPx = foreground.data[fY * foreground.step + fX * foreground.channels() + c];
				unsigned char backgroundPx = background.data[y * background.step + x * background.channels() + c];
				if (disparityMap.data[(y)* disparityMap.step + (x + dis) * disparityMap.channels()] < disparity)
				{
					output.data[y*output.step + output.channels()*x + c] = foregroundPx;
				}
			}
		}
	}

	imshow("outputR", output);
	imwrite("outputR.jpg", output);
	waitKey(0);
	return;
}