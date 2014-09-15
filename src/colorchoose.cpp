/*
 * Framing credit to Shermal Fernando
 * http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>

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

void addHSVThresholdBars(string window_name, int iLowH, int iHighH, int iLowS,
		int iHighS, int iLowV, int iHighV) {

	//Create trackbars in "Control" window
	createTrackbar("LowH", window_name, &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", window_name, &iHighH, 179);

	createTrackbar("LowS", window_name, &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", window_name, &iHighS, 255);

	createTrackbar("LowV", window_name, &iLowV, 255); //Value (0 - 255)
	createTrackbar("HighV", window_name, &iHighV, 255);

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

int main_ccr(int argc, char** argv) {

	VideoCapture cap = openCamera(0);

	createWindow("Control");

	int iLowH = 38;
	int iHighH = 75;

	int iLowS = 150;
	int iHighS = 255;

	int iLowV = 50;
	int iHighV = 255;
	addHSVThresholdBars("Control", iLowH, iHighH, iLowS, iHighS, iLowV, iHighV);

	int iLastX = -1;
	int iLastY = -1;

	//Create a black image with the size as the camera output
	//on which the red lines are drawn. Layered over original.
	Mat imgLines = getBlankFromCam(cap);

	while (true) {

		Mat imgOriginal;
		bool bSuccess = readFrame(cap, &imgOriginal);

		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),
				Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);

		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;

		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
		if (dArea > 10000) {
			//calculate the position of the ball
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

		if (waitKey(5) == 27) //wait for 'esc' key press for 5ms. If 'esc' key is pressed, break loop
				{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;
}
