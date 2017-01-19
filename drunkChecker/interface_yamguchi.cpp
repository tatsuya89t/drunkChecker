//
//  interface_yamguchi.cpp
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#include "interface_yamguchi.h"

//
//typedef struct Drunker {
//    int x_min, x_max;   //人領域の横幅
//    int y_min, y_max;   //人領域の縦幅
//    int flug;
//    Mat result_img;
//};

void showResult(Drunker drunk){
    
    Mat result;
    char* nameb1 = "button1";
    int center_x = 0;
    int center_y = 0;
    
    Mat icon = imread("../../../../../img/dangerIcon.png");
    
    result = drunk.result_img.clone();
    if(icon.empty()){
        printf("Don't read a image file!\n");
        imshow("resultFinal", result);
        return;
    }
    
    drunk.flug = 1;
    drunk.x_min = 500;
    drunk.x_max = 1000;
    drunk.y_min = 100;
    drunk.y_max = 200;
    center_x = (drunk.x_max+drunk.x_min)/2;
    center_y = (drunk.y_max+drunk.y_min)/2;
    
    if (drunk.flug == 1) {
        printf("hit\n");
        result = PinP_tr(result, icon, center_x, center_y);
        printf("%d, %d\n", center_x, center_y);
    }
    
    createButton(nameb1, saveResult);
    
    imshow("resutlFinal", result);
    
}

void saveResult(int state, void* userdata){
    
}

// 画像を画像に貼り付ける関数
Mat PinP_tr(const cv::Mat &srcImg, const cv::Mat &smallImg, const int tx, const int ty)
{
    //背景画像の作成
    cv::Mat dstImg;
    srcImg.copyTo(dstImg);
    
    //前景画像の変形行列
    cv::Mat mat = (cv::Mat_<double>(2,3)<<1.0, 0.0, tx, 0.0, 1.0, ty);
    
    //アフィン変換の実行
    cv::warpAffine(smallImg, dstImg, mat, dstImg.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
    //imshow("affine", dstImg);
    return dstImg;
}