//
//  camera_maeda.cpp
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#include "camera_maeda.h"

Drunker camera(VideoCapture cap, Mat ground) {
    //飲酒者？情報の構造体
    Drunker d;
    
    //二値化画像保存用
    Mat bin_img;
    
    //入力映像用
    Mat frame;
    //映像の取得
    cap >> frame;
    if (frame.empty()) { //入力失敗の場合
        //fprintf(stderr, "File is not opened.\n");
        return d;
    }
    
    //背景差分
    bin_img = abs(frame, ground);
    
    //膨張収縮処理
    Mat d_img, e_img;
    dilate(bin_img, d_img, Mat(), Point(-1,-1),10);
    erode(d_img, e_img, Mat(), Point(-1,-1),10);
    
    //膨張収縮画像表示
    //imshow("result",e_img);
    
    //白領域のxy座標の最大値最小値
    d = Maxmin(bin_img, d);
    
    //テスト確認用
    // 入力映像の表示
    //imshow("Camera", frame);
    
    //背景画像表示
    //imshow("background", ground);
    
    //二値化画像表示
    //imshow("result",bin_img);
    
    d = Dist(d, bin_img);
    
    
    //検出結果画像を入力
    d.result_img = frame.clone();
    
    return d;
}


//背景差分
Mat abs(Mat frame, Mat ground){
    //結果画像用
    Mat result = Mat::zeros(frame.size().height, frame.size().width, CV_8UC1);
    
    //グレースケール用
    Mat dst_f, dst_g;
    //二値化用
    Mat bin_img;
    //フレーム画像と背景画像のグレースケール変換
    cvtColor(frame, dst_f,CV_BGR2GRAY);
    cvtColor(ground, dst_g,CV_BGR2GRAY);
    
    unsigned char s_f, s_g, ans; //差分計算用
    //背景差分
    for(int y=0; y<frame.size().height; y++){
        for(int x=0; x<frame.size().width; x++){
            s_f = dst_f.at<unsigned char>(y, x); //カメラ画素値の取得
            s_g = dst_g.at<unsigned char>(y, x); //背景画素値の取得
            ans = abs(s_g - s_f);
            if(ans<100){
                s_f = 0;
            }
            
            result.at<unsigned char>(y, x) = s_f;
        }
    }

    threshold(result, bin_img, 128 ,255, cv::THRESH_BINARY|cv::THRESH_OTSU);
    return bin_img;
}

//領域座標の算出
Drunker Maxmin(Mat bin_img, Drunker d){
    
    //人領域のx座標の最小値最大値
    d.x_min = bin_img.size().width;
    d.x_max = 0;
    //人領域のy座標の最小値最大値
    d.y_min = bin_img.size().height;
    d.y_max = 0;
    
    unsigned char s_f;
    
    for(int y=0; y<bin_img.size().height; y++){
        for(int x=0; x<bin_img.size().width; x++){
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
    
    //数値確認用
    //printf("%d, %d, %d, %d\n",d.x_min,d.x_max,d.y_min,d.y_max);
    
    return d;
}

//危険度
Drunker Dist(Drunker d, Mat bin_img){
    //危険ポイントとの距離
    int dist = bin_img.size().height/2-20;      //危険ポイント
    d.risk = pow((d.y_max-dist)*(d.y_max-dist),0.5);
    d.risk = d.risk/124.0;
    if(d.risk>=1.0){
        d.risk=1.0;
    }
    d.risk =(100-(d.risk*100));
    //printf("%.3f\n", d.risk); //危険度をパーセントで表示
    
    //一定の危険度になったら警告
    if(d.risk > 70.0){
        d.flug=1;
    }else{
        d.flug=0;
    }
    return d;
}