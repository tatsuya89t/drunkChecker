//
//  main.cpp
//  drunkChecker
//
//  Created by sawanolab on 2016/12/21.
//  Copyright (c) 2016年 AIT. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
    //カメラ映像の表示用
    Mat frame;
    //映像の宣言
    VideoCapture cap(0);
    // キャプチャのエラー処理
    if (!cap.isOpened()) return -1;
    
    Mat ground; //背景画像用
    cap >> ground;  //初期画像の取得
    
    while (1) {
        // カメラ映像の取得
        cap >> frame;
        // 映像の表示
        imshow("Camera", frame);
        
        // キー入力
        int key=waitKey(30);
        //終了キー
        if (key == 'q' || key == 'Q')   break;
        
        //背景画像の更新用ボタン
        if(key == 's'){
            ground=frame.clone();
        }
        //背景画像表示
        imshow("background", ground);
    }
    
    return 0;
}
