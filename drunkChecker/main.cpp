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
    
    //動画の総フレーム数取得
    int max = cap.get(CAP_PROP_FRAME_COUNT);
    int now;//現在のフレーム
    //背景画像の入力
    cap >> ground;
    
    if (ground.empty()) { //入力失敗の場合
        fprintf(stderr, "File is not opened.\n");
        return (-1);
    }
    
    while(1){
        //ループ再生
        now = cap.get(CAP_PROP_POS_FRAMES);
        if( now >= max-4 )
        {
            cap.set( CAP_PROP_POS_FRAMES , 0 );
        }
        //printf("%d %d\n",now,max-4);
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
