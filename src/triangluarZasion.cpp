/*
 * Framing credit to Shermal Fernando
 * http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int unworked_triag(int argc, char** argv) {
	VideoCapture cap(0); //capture the video from webcam
	VideoCapture cap1(2);
	VideoCapture cap2(1);
//
//	if (!cap2.isOpened())  // if not success, exit program
//	{
//		cout << "Cannot open the web cam" << endl;
//		return -1;
//	}
//
	if (!cap1.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}


	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 38;
	int iHighH = 75;

	int iLowS = 150;
	int iHighS = 255;

	int iLowV = 50;
	int iHighV = 255;

	bool checkA = false;

	//Create trackbars in "Control" window
	createTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	createTrackbar("HighH", "Control", &iHighH, 179);

	createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	createTrackbar("HighS", "Control", &iHighS, 255);

	createTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	createTrackbar("HighV", "Control", &iHighV, 255);

	int iLastX = -1;
	int iLastY = -1;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);

	while (true) {
		int key = cvWaitKey(5);  //wait for 'esc' key press for 5ms. If 'esc' key is pressed, break loop

		if (key == 'a')
			checkA = !checkA;
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
//
//		Mat imgHSV;
//
//		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
//
//		Mat imgThresholded;
//
//		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),
//				Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
//
//		//morphological opening (removes small objects from the foreground)
//		erode(imgThresholded, imgThresholded,
//				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		dilate(imgThresholded, imgThresholded,
//				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//morphological closing (removes small holes from the foreground)
//		dilate(imgThresholded, imgThresholded,
//				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//		erode(imgThresholded, imgThresholded,
//				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
//		//Calculate the moments of the thresholded image
//		Moments oMoments = moments(imgThresholded);
//
//		double dM01 = oMoments.m01;
//		double dM10 = oMoments.m10;
//		double dArea = oMoments.m00;
//
//		// if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
//		if (checkA)
//			if (dArea > 10000) {
//			//calculate the position of the ball
//			int posX = dM10 / dArea;
//			int posY = dM01 / dArea;
//			if (dArea){
//
//				cout << dM01<< "\t" << posY<<"\t" << dArea << endl;
//			}
//			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0) {
//				//Draw a red line from the previous point to the current point
//				line(imgLines, Point(posX, posY), Point(iLastX, iLastY),
//						Scalar(0, 0, 255), 2);
//			}
//
//			iLastX = posX;
//			iLastY = posY;
//		}
//
//		imshow("Thresholded Image", imgThresholded); //show the thresholded image
//		imgOriginal = imgOriginal + imgLines;
//		imshow("Original", imgOriginal); //show the original image
//		Mat imgReflected;
//		cv::flip(imgOriginal, imgReflected, 1);
//		imshow("Reflected", imgReflected); //show the reflected image
		Mat newthing;
		cap.read(newthing);
		imshow("name", newthing);
		cap1.read(newthing);
		imshow("name1", newthing);
		//imshow("name2", cap2.read(newthing));

		if (key == 27){
			cout << "esc key is pressed by user" << endl;
			break;
		}

	}

	return 0;
}
