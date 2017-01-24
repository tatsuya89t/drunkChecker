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
//  int x_min, x_max;   //人領域の横幅
//  int y_min, y_max;   //人領域の縦幅
//  int flug;           //距離の危険フラグ
//  int flug_step;      //千鳥足の危険フラグ
//  float risk;         //危険度
//  Mat result_img;
//  int *param;         //ラベリング用　連結部分の情報の面積とか入れる
//
//  int num[353];       //千鳥足取得用
//  int sum_count;      //取得回数の合計値
//  int sum_coord;      //取得座標の合計値
//  int avr;            //取得座標の平均値
//};

int resultNum=0;

void showResult(Drunker drunk){
    
    Mat result;
    int center_x = 0;
    int center_y = 0;
    Scalar s = Scalar(200,0,0);
    
    //バー用変数
    //Mat img = cv::Mat::zeros(500, 500, CV_8UC3);
    Point bar1 = Point(0, drunk.result_img.size().height-20);
    Point bar2;
    
    char resultFile[100];
    //char* jpg = ".jpg";
    
    Size img_size = drunk.result_img.size();
    
    Point textPoint = Point(10, drunk.result_img.size().height+30);
    
    Mat icon = imread("../../../../../img/dangerIcon.png");
    
    result = Mat::zeros(drunk.result_img.size().height+80, drunk.result_img.size().width, CV_8UC3);
    cv::Vec3b s_vec; //色値
    
    for(int y=0; y<drunk.result_img.size().height+80; y++){
        for(int x=0; x<drunk.result_img.size().width; x++){
            if(y>=0 && y<drunk.result_img.size().height){
                s_vec = drunk.result_img.at<Vec3b>(y, x); //カメラ画素値の取得
            }else{
                s_vec = 0;
            }
            result.at<cv::Vec3b>(y, x) = s_vec;
        }
    }
    //result = drunk.result_img.clone();
    if(icon.empty()){
        printf("Don't read a image file!\n");
        imshow("resultFinal", result);
        return;
    }
    
    //drunk.flug = 1;
//    drunk.x_min = 500;
//    drunk.x_max = 1000;
//    drunk.y_min = 100;
//    drunk.y_max = 200;
    center_x = (drunk.x_max+drunk.x_min)/2;
    center_y = (drunk.y_max+drunk.y_min)/2;
    
    //バーの長さを決定
    bar2 = Point(getBarWidth(drunk.result_img, drunk.risk), drunk.result_img.size().height);
    
    //危険フラグがある時，対象の近くに注意マークを付与
    if (drunk.flug == 1) {
        //printf("hit\n");
        result = PinP_tr(result, icon, center_x, center_y);
        //printf("%d, %d\n", center_x, center_y);
    }
    
    //バーの長さによって色を変更
    if (50 < drunk.risk && drunk.risk < 70) {
        s = Scalar(0,200,0);
    }
    else if (drunk.risk > 70){
        s = Scalar(0,0,200);
    }
    
    
    //printf("%d, %d\n", drunk.result_img.size().width);
    
    rectangle(result, bar1, bar2, s, -1, CV_AA);
    line(result, Point(img_size.width/2+100, 0), Point(img_size.width/2+100, img_size.height), Scalar(0, 0, 200));
    
    cv::putText(result, "If input a 's' key,", textPoint, FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,200), 2, CV_AA);
    textPoint.y = drunk.result_img.size().height+50;
    cv::putText(result, "save a capture image.", textPoint, FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0,0,200), 2, CV_AA);
    
    //保存用ファイル名を作成
    sprintf(resultFile, "../../../../../img/result/result%d.jpg", resultNum);
    // キー入力
    int keys=waitKey(30);
    //終了キー
    if (keys == 's'){
        imwrite(resultFile, result);
        resultNum++;
    }
    
    imshow("resultFinal", result);
    
}

//％バーの長さを算出
int getBarWidth(Mat img, int res){
    
    float w = 0;
    //int max = 20;
    float parWidth = (float)img.size().width / 100.0;
    int maxWidth = (int)res;
    
    for (int i=0; i<=maxWidth; i++) {
        w += parWidth;
        if (w > img.size().width) {
            w = img.size().width;
        }
    }
    
    printf("%f ,%d, %f\n", parWidth, img.size().width, w);
    
    return (int)w;
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