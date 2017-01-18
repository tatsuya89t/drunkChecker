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
Mat camera(VideoCapture cap);

int main(int argc, const char * argv[]) {
    VideoCapture cap(0);
    Mat result;
    while(1){
        result = camera(cap);   //前田担当
        imshow("result",result);
        
        // キー入力
        int key=waitKey(30);
        //終了キー
        if (key == 'q' || key == 'Q')   break;
        
    }
    return 0;
}
