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
    //画像の入力
    Mat frame, size;
    //映像の宣言
    VideoCapture cap(0);
    // キャプチャのエラー処理
    if (!cap.isOpened()) return -1;
    
    while (1) {
        // カメラ映像の取得
        cap >> frame;
        // 映像の表示
        imshow("Camera", frame);
        // キー入力があれば終了
        if (waitKey(30) >= 0) break;
    }
    
    return 0;
}
