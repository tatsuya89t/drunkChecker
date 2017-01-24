//
//  camera_maeda.cpp
//  drunkChecker
//
//  Created by x12101xx on 2017/01/18.
//  Copyright (c) 2017年 AIT. All rights reserved.
//

#include "camera_maeda.h"

Drunker camera(Drunker d, VideoCapture cap, Mat ground) {
    //二値化画像保存用
    Mat bin_img;
    
    //入力映像用
    Mat frame;
    //映像の取得
    cap >> frame;
    
    //背景差分
    bin_img = abs(frame, ground);
    
    //膨張収縮処理
    Mat d_img, e_img;
    dilate(bin_img, d_img, Mat(), Point(-1,-1),10);
    erode(d_img, e_img, Mat(), Point(-1,-1),10);
    //膨張収縮画像表示
    //imshow("result",e_img);
    
    //ラベリング処理
    //rabering(d,e_img);
    
    //白領域のxy座標の最大値最小値
    d = Maxmin(e_img, d);
    
    //危険度みたいな数値の取得処理
    d = Dist(d, e_img);
    
    //千鳥足を検出する予定
    //d = T_step(d, e_img);
    
    //テスト確認用
    // 入力映像の表示
    //imshow("Camera", frame);
    
    //背景画像表示
    //imshow("background", ground);
    
    //二値化画像表示
    imshow("result",e_img);
    
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
            if(ans<50){
                s_f = 0;
            }
            
            result.at<unsigned char>(y, x) = s_f;
        }
    }

    threshold(result, bin_img, 200 ,255, cv::THRESH_BINARY|cv::THRESH_OTSU);
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
    int dist = bin_img.size().width/2+100;      //危険ポイント
    d.risk = pow((d.x_max-dist)*(d.x_max-dist),0.5);
    d.risk = d.risk/124.0;
    if(d.risk>=1.0){
        d.risk=1.0;
    }
    d.risk =(100-(d.risk*100));
    //printf("%.3f\n", d.risk); //危険度をパーセントで表示
    
    //一定の危険度になったら警告フラグをON
    if(d.risk > 70.0){
        d.flug=1;
    }else{
        d.flug=0;
    }
    return d;
}

//ラベリング処理
Drunker rabering(Drunker d, Mat e_img){
    // ラベル用画像生成(※CV_32S or CV_16Uにする必要あり)
    Mat labelImage(e_img.size(), CV_32S);
    Mat stats;
    Mat centroids;
    
    // ラベリング実行．戻り値がラベル数．また，このサンプルでは8近傍でラベリングする．
    int nLabels = connectedComponentsWithStats(e_img, labelImage, stats, centroids, 8);
    
    // ラベリング結果の描画色を決定
    std::vector<Vec3b> colors(nLabels);
    colors[0] = Vec3b(0, 0, 0);
    for(int label = 1; label < nLabels; ++label){
        d.param = stats.ptr<int>(label);
        //ConnectedComponentsTypes::CC_STAT_AREA = 4    //連結している部分の総面積の引数
        //人の面積の色指定
        if(d.param[4]> 20 && d.param[4]< 2000){
            colors[label] = Vec3b(0, 0, 255);
        }
        //その他の面積の色指定
        //        }else if(param[4]>5000 && param[4]< 30000){
        //            colors[label] = Vec3b(255, 0, 0);
        //        }
    }
    
//    // ラベリング結果の描画
//    Mat dst(e_img.size(), CV_8UC3);
//    for(int y = 0; y < dst.rows; ++y){
//        for(int x = 0; x < dst.cols; ++x){
//            int label = labelImage.at<int>(y, x);
//            Vec3b &pixel = dst.at<Vec3b>(y, x);
//            pixel = colors[label];
//        }
//    }
//    
//    //面積値の出力
//    for (int i = 1; i < nLabels; ++i) {
//        d.param = stats.ptr<int>(i);
//        std::cout << "area "<< i <<" = " << d.param[4] << std::endl;
//        
//        //ROIの左上に番号を書き込む
//        int x = d.param[0];   //cv::ConnectedComponentsTypes::CC_STAT_LEFT=0  一番左上のx座標
//        int y = d.param[1];   //cv::ConnectedComponentsTypes::CC_STAT_TOP=1   一番左上のy座標
//        std::stringstream num;
//        num << i;
//        cv::putText(dst, num.str(), cv::Point(x+5, y+20), cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0, 255, 255), 2);
//    }
    return d;
}

//千鳥足検出
Drunker T_step(Drunker d, Mat bin_img){
    int ans=0;  // 人の中心x座標計算用
    ans = (d.x_min+d.x_max)/2;  //(最小値+最大値)/2
    //画面外は取得しない
    if(ans<bin_img.size().width && ans>=0){
        d.num[ans]++;                       //x座標の取得回数を加算
        d.sum_count++;                      //x座標の取得回数の合計を加算
        d.sum_coord = d.sum_coord + ans;    //x座標の取得座標の合計値
    }
    
    d.avr = int(d.sum_coord / d.sum_count);      //x座標の取得座標の平均値
    //printf("%d\n", d.avr);

    //
    
    //千鳥足の検出
    /*人の移動方向のx座標の中心を取り、左右に揺れている回数が一定を超えたら千鳥足のはず*/
    for(int i=0; i<bin_img.size().width; i++){
        if(i<d.avr-40){
            d.tstep_left_sum=d.tstep_left_sum + d.num[i];
        }else if(i>d.avr+40){
            d.tstep_right_sum=d.tstep_right_sum + d.num[i];
        }
    }
    //printf("%d , %d\n", d.tstep_left_sum, d.tstep_right_sum);
    
//    if(d.tstep_left_sum>5 && d.tstep_right_sum>5){
//        d.flug=1;
//    }else{
//        d.flug=0;
//    }
    
    return d;
}