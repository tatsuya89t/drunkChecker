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
    VideoCapture cap(0);
    Mat ground, result;
    Drunker drunker;
    
    cap >> ground;
    
    while(1){
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
