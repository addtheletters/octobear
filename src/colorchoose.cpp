/*
 * Framing credit to Shermal Fernando
 * http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <stdio.h>

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

void addHSVThresholdBars(string window_name, int* iLowH, int* iHighH, int* iLowS,
		int* iHighS, int* iLowV, int* iHighV) {

	//Create trackbars in "Control" window
	createTrackbar("LowH", window_name, iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", window_name, iHighH, 179);

	createTrackbar("LowS", window_name, iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", window_name, iHighS, 255);

	createTrackbar("LowV", window_name, iLowV, 255); //Value (0 - 255)
	createTrackbar("HighV", window_name, iHighV, 255);

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

void morph(Mat* img) {
	//morphological opening (removes small objects from the foreground)
	erode(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (removes small holes from the foreground)
	dilate(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
}

Mat imgOriginal;
Mat imgHSV;

int ensurePositive(int val){
	if (val < 0){
		return 0;
	}
	return val;
}

int ensureCapped(int val, int cap){
	if (val > cap){
		return cap;
	}
	return val;
}

int* getThreshold( int h, int s, int v ){
	int retthresh[ 6 ];
	//these will need lots of tweaking
	//especially saturation and value
	//probably more arguments too.

	retthresh[0] = ensurePositive(h-20);
	retthresh[1] = ensureCapped(h+20, 179);
	retthresh[2] = ensurePositive(s-10);
	retthresh[3] = ensureCapped(s+10, 255);
	retthresh[4] = ensurePositive(v-10);
	retthresh[5] = ensureCapped(v+10, 255);
	return retthresh;
}


void onMouse(int event, int x, int y, int flags, void* usrdata) {
	//cout << "NOOO" << endl;

	if (event != EVENT_LBUTTONDOWN) {
		return;
	}

	cout << "LMB clicked at (" << x << "," << y << ")" << endl;
	Vec3b bgrPixel = imgOriginal.at<Vec3b>(y, x);
	//cout is LITERALLY HITLER (on my laptop)
	//cout << "BGR color is [" << bgrPixel.val[0] << "," << bgrPixel.val[1] << ","
	//		<< bgrPixel.val[2] << "]" << endl;
	printf("BGR color is [%d, %d, %d]\n", bgrPixel.val[0], bgrPixel.val[1], bgrPixel.val[2]);
	Vec3b hsvPixel = imgHSV.at<Vec3b>(y, x);
	//cout << "HSV color is [" << hsvPixel.val[0] << "," << hsvPixel.val[1] << ","
	//		<< hsvPixel.val[2] << "]" << endl;
	printf("HSV color is [%d, %d, %d]\n", hsvPixel.val[0], hsvPixel.val[1], hsvPixel.val[2]);

	//printfs alone were not giving output until the next cout was reached
	cout << "force out?" << endl;
}

int main(int argc, char** argv) {

	VideoCapture cap = openCamera(0);

	createWindow("Ctrl");
	createWindow("Original");
	setMouseCallback("Original", onMouse, 0);

	int iLowH = 38;
	int iHighH = 75;

	int iLowS = 70;
	int iHighS = 255;

	int iLowV = 50;
	int iHighV = 255;
	addHSVThresholdBars("Ctrl", &iLowH, &iHighH, &iLowS, &iHighS, &iLowV, &iHighV);

	int iLastX = -1;
	int iLastY = -1;

	//Create a black image with the size as the camera output
	//on which the red lines are drawn. Layered over original.
	Mat imgLines = getBlankFromCam(cap);

	while (true) {

		//Mat imgOriginal; // global now so onmouse can access easily
		readFrame(cap, &imgOriginal);

		//imgHSV; //global now so onmouse can access easily
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),
				Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		morph(&imgThresholded);

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01; // area * the ypos of 'center' of all white marks
		double dM10 = oMoments.m10; // area * the xpos of 'center' of all white marks
		double dArea = oMoments.m00; // area

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
		if (dArea > 10000) {
			//calculate the position of the blob
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;

			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0) {
				//Draw a red line from the previous point to the current point
				line(imgLines, Point(posX, posY), Point(iLastX, iLastY),
						Scalar(0, 0, 255), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		imgOriginal = imgOriginal + imgLines;
		imshow("Original", imgOriginal); //show the original image
		Mat imgReflected;
		cv::flip(imgOriginal, imgReflected, 1);
		imshow("Reflected", imgReflected); //show the reflected image

		if (waitKey(1) == 27) //wait for 'esc' key press for 5ms. If 'esc' key is pressed, break loop
				{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
