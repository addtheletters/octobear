#include <iostream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

VideoCapture openCamera(int num) {
	VideoCapture cam(num); //capture the video from webcam

	if (!cam.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
	}

	return cam;
}

void createWindow(string window_name) {
	namedWindow(window_name, CV_WINDOW_AUTOSIZE); //create a window called "Control"
}


Mat getBlankFromCam(VideoCapture cam) {
	//Capture a temporary image from the camera
	Mat imgTmp;
	cam.read(imgTmp);
	Mat blank = Mat::zeros(imgTmp.size(), CV_8UC3); //zeroed matrix of same size
	return blank;
}

bool readFrame(VideoCapture cam, Mat* frame) {
	bool success = cam.read(*frame);

	if (!success)
		cout << "Cannot read a frame from video stream" << endl;
	return success;
}

