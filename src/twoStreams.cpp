#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <stdarg.h>
#include "opencv2/imgproc/imgproc_c.h"
#include <unistd.h>

using namespace std;
char key;

int main()
{
    //cvNamedWindow("Camera_Output", 1);    //Create window
    //cvNamedWindow("Camera2_Output", 1);
    cv::VideoCapture camera0(1); //thanks, https://stackoverflow.com/questions/13925867/displaying-multiple-camera-feeds-simultaneously-with-opencv
    cv::VideoCapture camera1(2);
    while(1){ //Create infinte loop for live streaming
        /*CvCapture* capture = cvCaptureFromCAM(1);
        cvShowImage("Camera_Output", capture);
        cvReleaseCapture(&capture);
        usleep(100);
        CvCapture* capture2 = cvCaptureFromCAM(2);
        cvShowImage("Camera_Output2", capture2);
        cvReleaseCapture(&capture2);*/

        //cv::VideoCapture camera0(0);
        cv::Mat3b frame0;
        camera0 >> frame0;
        cv::imshow("Video0", frame0);
        //camera0.release();
        //cv::VideoCapture camera1(1);
        cv::Mat3b frame1;
        camera1 >> frame1;
        cv::imshow("Video1", frame1);
        //camera1.release() //"works"

        //cvShowManyImages("Camera_Output", 2, frame0, frame1);   //Show image frames on created window
        key = cvWaitKey(10);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    //cvReleaseCapture(&capture); //Release capture.
    //cvDestroyWindow("Camera_Output"); //Destroy Window
    //cvDestroyWindow("Camera_Output2");
    return 0;
}
//From: http://opencvlover.blogspot.com/2011/07/accesing-camera-using-opencv.html
