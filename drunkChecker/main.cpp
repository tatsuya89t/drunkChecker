//
//  main.cpp
//  drunkChecker
//
//  Created by sawanolab on 2016/12/21.
//  Copyright (c) 2016年 AIT. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera_maeda.h"
#include "interface_yamguchi.h"

using namespace cv;

int main(int argc, const char * argv[]) {
    
    
    //VideoCapture cap(0);  //PCのカメラ入力
    VideoCapture cap("../../../../../mov/00060_2.mp4");   //動画ファイル入力
    Mat ground; //= imread("../../../../../img/ground.png");   //背景画像
    Mat result;
    Drunker drunker;
    
    //背景画像の入力
    cap >> ground;
    
    if (ground.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    while(1){
        //動画終了した時用
        if(cv::waitKey(30) >= 0 || cap.get(CV_CAP_PROP_POS_AVI_RATIO) == 1){
            waitKey();
            break;
        }
        drunker = camera(cap, ground);   //前田担当
        
        //imshow("result2",drunker.result_img);
        
        showResult(drunker);
        
        // キー入力
        int key=waitKey(30);
        //終了キー
        if (key == 'q' || key == 'Q')   break;
        
    }
    
    return 0;
}
