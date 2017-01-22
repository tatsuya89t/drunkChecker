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
    int flug;           //距離の危険フラグ
    int flug_step;      //千鳥足の危険フラグ
    float risk;         //危険度
    Mat result_img;
    int *param;         //ラベリング用　連結部分の情報の面積とか入れる
    
    int num[353];       //千鳥足取得用
    int sum_count;      //取得回数の合計値
    int sum_coord;      //取得座標の合計値
    int avr;            //取得座標の平均値
    
};

Drunker camera(Drunker d, VideoCapture cap, Mat ground);
Mat abs(Mat frame, Mat ground);
Drunker Maxmin(Mat bin_img, Drunker d);
Drunker Dist(Drunker d, Mat bin_img);
Drunker rabering(Drunker d, Mat bin_img);
Drunker T_step(Drunker d, Mat bin_img);
#endif /* defined(__drunkChecker__camera_maeda__) */
