//
//  camera_maeda.cpp
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#include "camera_maeda.h"

Drunker camera(VideoCapture cap, Mat ground) {
    
    //カメラ映像の表示用
    Mat frame;
    
    //グレースケール用
    Mat dst_f, dst_g;
    
    // カメラ映像の取得
    cap >> frame;
    //結果画像
    Mat result = Mat::zeros(frame.size().height, frame.size().width, CV_8UC1);
    Drunker d;
    
    //映像の宣言
    // キャプチャのエラー処理
    if (!cap.isOpened()) return d;
    
    unsigned char s_f, s_g; //色値
    
    cvtColor(frame, dst_f,CV_BGR2GRAY);
    cvtColor(ground, dst_g,CV_BGR2GRAY);
    
    for(int y=0; y<frame.size().height; y++){
        for(int x=0; x<frame.size().width; x++){
            s_f = dst_f.at<unsigned char>(y, x); //カメラ画素値の取得
            s_g = dst_g.at<unsigned char>(y, x); //背景画素値の取得
            if(s_f==s_g){
                s_f = 0;
            }
            
            result.at<unsigned char>(y, x) = s_f;
        }
    }
        
    //テスト確認用
    // 映像の表示
    imshow("Camera", frame);
    //背景画像表示
    imshow("background", ground);
    
    imshow("result",result);
    
    d.result_img = result.clone();
    
    return d;
}