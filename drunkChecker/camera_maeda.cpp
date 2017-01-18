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
    
    //二値化
    Mat bin_img;
    
    // カメラ映像の取得
    cap >> frame;
    //結果画像
    Mat result = Mat::zeros(frame.size().height, frame.size().width, CV_8UC1);
    Drunker d;
    
    //映像の宣言
    // キャプチャのエラー処理
    if (!cap.isOpened()) return d;
    
    unsigned char s_f, s_g, ans; //色値
    
    //フレーム画像と背景画像のグレースケール変換
    cvtColor(frame, dst_f,CV_BGR2GRAY);
    cvtColor(ground, dst_g,CV_BGR2GRAY);
    
    //背景差分
    for(int y=0; y<frame.size().height; y++){
        for(int x=0; x<frame.size().width; x++){
            s_f = dst_f.at<unsigned char>(y, x); //カメラ画素値の取得
            s_g = dst_g.at<unsigned char>(y, x); //背景画素値の取得
            ans = abs(s_f - s_g);
            if(ans<20){
                s_f = 0;
            }
            
            result.at<unsigned char>(y, x) = s_f;
        }
    }
    
    threshold(result, bin_img, 128 ,255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    
    
    //領域座標の算出
    //人領域のx座標の最小値最大値
    d.x_min = frame.size().width;
    d.x_max = 0;
    //人領域のy座標の最小値最大値
    d.y_min = frame.size().height;
    d.y_max = 0;
    
    for(int y=0; y<frame.size().height; y++){
        for(int x=0; x<frame.size().width; x++){
            s_f = bin_img.at<unsigned char>(y, x); //カメラ画素値の取得
            if(s_f == 255){
                if(x<d.x_min){
                    d.x_min = x;
                }
                if(x>d.x_max){
                    d.x_max = x;
                }
                if(y<d.y_min){
                    d.y_min = y;
                }
                if(x>d.y_max){
                    d.y_max = y;
                }
            }
        }
    }
    
    //テスト確認用
    // 映像の表示
    imshow("Camera", frame);
    //背景画像表示
    imshow("background", ground);
    
    imshow("result",bin_img);
    
    d.result_img = result.clone();
    
    return d;
}