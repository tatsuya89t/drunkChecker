//
//  camera_maeda.cpp
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#include "camera_maeda.h"
using namespace cv;

Mat camera(VideoCapture cap) {
    
    //カメラ映像の表示用
    Mat frame;
    // カメラ映像の取得
    cap >> frame;
    //結果画像
    Mat result=Mat::zeros(frame.size().height, frame.size().width, CV_8U);
    
    //映像の宣言
    // キャプチャのエラー処理
    if (!cap.isOpened()) return result;
    
    
    Mat ground; //背景画像用
    cap >> ground;  //初期画像の取得
    
    //テスト確認用
    // 映像の表示
    imshow("Camera", frame);
    //背景画像表示
    imshow("background", ground);
    
    return result;
}