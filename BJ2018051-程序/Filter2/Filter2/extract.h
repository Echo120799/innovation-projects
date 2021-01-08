#pragma once
//
//  extract.h
//  OpencvTest
//
//  Created by L on 2020/4/17.
//  Copyright © 2020 L. All rights reserved.
//

#ifndef extract_h
#define extract_h
#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

void extract(Mat &img, Mat &mask, int disparity)
{

	cout << "img.rows" << img.rows << ";";
	cout << "img.cols" << img.cols << endl;
	//cout<<img;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{

			if ((int)(*(img.data + img.step[0] * i + img.step[1] * j)) > disparity)
			{
				//cout<<"i="<<i<<";j="<<j<<endl;
				*(mask.data + mask.step[0] * i + mask.step[1] * j) = 255;
			}
			else
				*(mask.data + mask.step[0] * i + mask.step[1] * j) = 0;

		}
	}

}

#endif /* extract_h */
