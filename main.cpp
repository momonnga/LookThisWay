//
//  main.cpp
//  CameraOpticalFlow
//
//  Created by MasayukiTamura on 2017/07/17.
//  Copyright © 2017年 MasayukiTamura. All rights reserved.
//

#include <highgui.hpp>
#include <imgproc.hpp>
//#include <objdetect\objdetect.hpp>
#include <video/tracking.hpp>
#include <vector>
#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <iostream>
#include <core.hpp>
#include <highgui.hpp>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


using namespace cv;
using namespace std;

#define PATHNAME_SIZE 512

#include "opencv2/opencv.hpp"

using namespace cv;


/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */

String face_cascade_name = "./haarcascade_frontalface_alt.xml";
String eyes_cascade_name = "./haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
#include <unistd.h>
#include <sys/param.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
std::vector<Rect> faces;
float sumDistX=0.0f;
float sumDistY=0.0f;
int dirF=0;
int ansdirF=1;
int main(int, char**)
{
    // add your file name
    // 変数定義
    char pathname[PATHNAME_SIZE];  // ファイルパス
    // カレントディレクトリ取得
    getcwd(pathname, PATHNAME_SIZE);
    //fprintf(stdout,"現在のファイルパス:%s\n", pathname);
    //VideoCapture cap("mv28.mp4");
    
    
    Mat flow, frame;
    // some faster than mat image container
    UMat  flowUmat, prevgray;
    //
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n");
        fprintf(stdout,"現在のファイルパス:%s\n", pathname);return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };
    
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    
    Mat edges;
    namedWindow("edges",1);
    //Mat frame;
    Mat img;
    Mat original;
    Mat bef;
    int t=850;
    //int t=0;
    int minust=50;
    int timeFlag=0;
    //Mat white_img(cv::Size(640, 480), CV_8UC1, cv::Scalar::all(255));
    for(;;)
    {
        if(t>=800||(175-minust<t&&t<=190-minust)){
            //Mat frame;
            cap >> frame; // get a new frame from camera
            //
            sumDistX=0.0f;
            sumDistY=0.0f;
            //Mat img;
            //Mat original;
            img=frame;
            // capture frame from video file
            ///cap.retrieve(frame, CV_CAP_OPENNI_BGR_IMAGE);
            resize(img, img, Size(640, 480));
            
            // save original for later
            img.copyTo(original);
            
            detectAndDisplay( original );
            
            // just make current frame gray
            cvtColor(img, img, COLOR_BGR2GRAY);
            
            if (prevgray.empty() == false ) {
                
                // calculate optical flow
                calcOpticalFlowFarneback(prevgray, img, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
                // copy Umat container to standard Mat
                flowUmat.copyTo(flow);
                
                
                // By y += 5, x += 5 you can specify the grid
                for (int y = 0; y < original.rows; y += 5) {
                    for (int x = 0; x < original.cols; x += 5)
                    {
                        // get the flow from y, x position * 10 for better visibility
                        const Point2f flowatxy = flow.at<Point2f>(y, x) * 10;
                        if(faces[0].x!=0){
                            if(faces[0].x<x&&x<faces[0].x+faces[0].width&&faces[0].y<y&&y<faces[0].y+faces[0].height){
                                sumDistX+=flowatxy.x;
                                sumDistY+=flowatxy.y;
                                
                            }
                        }
                    }
                }
                for (int y = 0; y < original.rows; y += 5) {
                    for (int x = 0; x < original.cols; x += 5)
                    {
                        // get the flow from y, x position * 10 for better visibility
                        const Point2f flowatxy = flow.at<Point2f>(y, x) * 10;
                        if(abs(sumDistX)>abs(sumDistY)){
                            if(sumDistX>30000&&faces[0].x<x&&x<faces[0].x+faces[0].width&&faces[0].y<y&&y<faces[0].y+faces[0].height){
                                // draw line at flow direction
                                line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(255,0,0));
                                if((175-minust<t&&t<=190-minust)&&timeFlag==3){
                                    dirF=1;
                                }
                                
                            }else if(sumDistX<-30000&&faces[0].x<x&&x<faces[0].x+faces[0].width&&faces[0].y<y&&y<faces[0].y+faces[0].height) {
                                line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(0,255,0));
                                if((175-minust<t&&t<=190-minust)&&timeFlag==3){
                                    dirF=2;
                                }
                            }
                        }else{
                            if(sumDistY>30000&&faces[0].x<x&&x<faces[0].x+faces[0].width&&faces[0].y<y&&y<faces[0].y+faces[0].height){
                                // draw line at flow direction
                                line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(0,0,255));
                                if((175-minust<t&&t<=190-minust)&&timeFlag==3){
                                    dirF=3;
                                }
                            }else if(sumDistY<-30000&&faces[0].x<x&&x<faces[0].x+faces[0].width&&faces[0].y<y&&y<faces[0].y+faces[0].height) {
                                line(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(0,255,255));
                                if((175-minust<t&&t<=190-minust)&&timeFlag==3){
                                    dirF=4;
                                }
                            }
                        }
                        // draw initial point
                        circle(original, Point(x, y), 1, Scalar(0, 0, 0), -1);
                        
                        
                        
                    }
                    
                }
                //detectAndDisplay( original );
                
                // draw the results
                namedWindow("prew", WINDOW_AUTOSIZE);
                imshow("prew", original);
                
                // fill previous image again
                img.copyTo(prevgray);
                
            }
            else {
                
                // fill previous image in case prevgray.empty() == true
                img.copyTo(prevgray);
                
            }
            
            
            
            //
            
            //cvtColor(frame, edges, CV_BGR2GRAY);
            //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
            //Canny(edges, edges, 0, 30, 3);
            //imshow("edges", edges);
            t++;
            printf("%d\n", t);
            
            if(t>900){
                t=0;
            }
            waitKey(50);
            //if(waitKey(30) >= 0) break;
        }else{
            //Mat original;
            Mat white_img(cv::Size(640, 480), CV_8UC1, cv::Scalar::all(255));
            int fontFace = FONT_HERSHEY_COMPLEX_SMALL;
            double fontScale = 1.5;
            int thickness = 2;
            Point textOrg(100, 100);
            //string someText = "Please wait";
            if(100-minust<t&&t<=125-minust){
                string someText1 = "Look";
                putText(white_img, someText1, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                timeFlag=1;
                printf("1:%d\n", t);
            }else if(125-minust<t&&t<=150-minust){
                string someText2 = "Look this";
                putText(white_img, someText2, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                timeFlag=2;
                printf("2:%d\n", t);
            }else if(150-minust<t&&t<175-minust){
                string someText3 = "Look this way!";
                putText(white_img, someText3, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                timeFlag=3;
                printf("3:%d\n", t);
                
            }else if(190-minust<t&&t<300-minust){
                timeFlag=5;
                Point textOrg2(100, 300);
                Point textOrg3(400, 300);
                if(dirF==ansdirF){
                    //string str1="You win!(you:";
                    //char str1[12] = "DRAGON";
                    //char str2[] = "QUEST";
                    //int i = 3;
                    //sprintf(str1,"%s%s%d\n",str1,str2,i);
                    //strcat(str1,dirF);
                    //string someText5 = "You win!(you:%s,com:"+ansdirF+")";
                    string someText5 = "You lose";
                    putText(white_img, someText5, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                    if(ansdirF==1){
                        string someText52 = "cpu:left";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==2){
                        string someText52 = "cpu:right";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==3){
                        string someText52 = "cpu:bottom";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==4){
                        string someText52 = "cpu:top";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }
                    if(dirF==1){
                        string someText53 = "you:left";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==2){
                        string someText53 = "you:right";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==3){
                        string someText53 = "you:bottom";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==4){
                        string someText53 = "you:top";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }
                    /*
                     string someText53 = "you:"+dirF;
                     putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                     */
                }else{
                    string someText5 = "You win";
                    putText(white_img, someText5, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                    if(ansdirF==1){
                        string someText52 = "cpu:left";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==2){
                        string someText52 = "cpu:right";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==3){
                        string someText52 = "cpu:bottom";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(ansdirF==4){
                        string someText52 = "cpu:top";
                        putText(white_img, someText52, textOrg2, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }
                    if(dirF==1){
                        string someText53 = "you:left";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==2){
                        string someText53 = "you:right";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==3){
                        string someText53 = "you:bottom";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }else if(dirF==4){
                        string someText53 = "you:top";
                        putText(white_img, someText53, textOrg3, fontFace, fontScale, Scalar::all(0), thickness,8);
                    }
                }
                
            }else if(350-minust<t&&t<400-minust){
                t=0;
                dirF=0;
                ansdirF = rand() % 4 + 1;
                
                //ansdirF=2;
                timeFlag=0;
            }else{
                string someText0 = "Please wait";
                putText(white_img, someText0, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
                printf("1:%d\n", t);
            }
            //putText(white_img, someText, textOrg, fontFace, fontScale, Scalar::all(0), thickness,8);
            //printf("%f\n", original.rows);
            //line(original, Point(100, 100), Point(cvRound(100 + 100), cvRound(100 + 100)), Scalar(0,255,255));
            namedWindow("prew", WINDOW_AUTOSIZE);
            imshow("prew", white_img);
            t++;
            printf("%d\n", t);
            waitKey(50);
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
Mat frame_gray;
Mat faceROI;
int radius;
/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    //std::vector<Rect> faces;
    //Mat frame_gray;
    
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    
    for( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        
        //Mat faceROI = frame_gray( faces[i] );
        faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        
        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    //imshow( window_name, frame );
}
