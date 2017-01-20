//
//  camera_maeda.h
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#ifndef __drunkChecker__camera_maeda__
#define __drunkChecker__camera_maeda__

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
struct Drunker {
    int x_min, x_max;   //人領域の横幅
    int y_min, y_max;   //人領域の縦幅
    int flug;           //危険アイコンのフラグ
    float risk;         //危険度
    Mat result_img;
};

Drunker camera(VideoCapture cap, Mat ground);
Mat abs(Mat frame, Mat ground);
Drunker Maxmin(Mat bin_img, Drunker d);
Drunker Dist(Drunker d, Mat bin_img);
#endif /* defined(__drunkChecker__camera_maeda__) */
