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
typedef struct Drunker {
    int x, y;
    int w, h;
    int flug;
    Mat result_img;
};

Drunker camera(VideoCapture cap);

#endif /* defined(__drunkChecker__camera_maeda__) */
