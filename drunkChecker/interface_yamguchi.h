//
//  interface_yamguchi.h
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#ifndef __drunkChecker__interface_yamguchi__
#define __drunkChecker__interface_yamguchi__

#include <stdio.h>
#include "camera_maeda.h"
#include <math.h>
#include <string.h>

void showResult(Drunker drunk);
void saveResult(int state, void* userdata);
Mat PinP_tr(const cv::Mat &srcImg, const cv::Mat &smallImg, const int tx, const int ty);
int getBarWidth(Mat img, int res);
void my_mouse_callback(int event, int x, int y, int flags, void* param);
#endif /* defined(__drunkChecker__interface_yamguchi__) */
