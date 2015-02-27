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
#include "bearhead.h"

using namespace cv;
using namespace std;

struct HSVThreshVals{
	int LowH;
	int HighH;
	int LowS;
	int HighS;
	int LowV;
	int HighV;
};



//everyone loves global variables
//*cough*

Mat imgOriginal;
Mat imgHSV;
Mat imgReflected;
Mat imgHSVReflected;

/*
int iLowH = 38;
int iHighH = 75;

int iLowS = 70;
int iHighS = 255;

int iLowV = 50;
int iHighV = 255;
*/
int drawcolor[] = {0, 0, 255};

int ASCII_CODE_ESCAPE = 27;
int ASCII_CODE_A_KEY = 97;

HSVThreshVals iThreshVals;



void addHSVThresholdBars(string window_name, HSVThreshVals* tvs) {

	//Create trackbars in "Control" window
	createTrackbar("LowH", window_name, &(tvs->LowH), 179); //Hue (0 - 179)
	createTrackbar("HighH", window_name, &(tvs->HighH), 179);

	createTrackbar("LowS", window_name, &(tvs->LowS), 255); //Saturation (0 - 255)
	createTrackbar("HighS", window_name, &(tvs->HighS), 255);

	createTrackbar("LowV", window_name, &(tvs->LowV), 255); //Value (0 - 255)
	createTrackbar("HighV", window_name, &(tvs->HighV), 255);

}

static void morph(Mat* img) {
	//morphological opening (removes small objects from the foreground)
	erode(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (removes small holes from the foreground)
	dilate(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(*img, *img, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
}

static void getPixelThreshold(int h, int s, int v, HSVThreshVals* retthresh) {
	//these will need lots of tweaking
	//especially saturation and value
	//probably more arguments too.
	retthresh->LowH = ensurePositive(h - 20);
	retthresh->HighH = ensureCapped(h + 20, 179);
	retthresh->LowS = ensurePositive(s - 30);
	retthresh->HighS = ensureCapped(s + 80, 255);
	retthresh->LowV = ensurePositive(v - 50);
	retthresh->HighV = ensureCapped(v + 80, 255);
	//return retthresh;
}

void setThreshold(HSVThreshVals threshvals){
	iThreshVals = threshvals;
	/*
	iThreshVals.LowH = threshvals[0];
	iThreshVals.HighH = threshvals[1];

	iThreshVals.LowS= threshvals[2];
	iThreshVals.HighH= threshvals[3];

	iThreshVals.LowV= threshvals[4];
	iThreshVals.HighV= threshvals[5];
	*/
}

static HSVThreshVals getHSVThreshold(Mat hsvImg, int x, int y){
	Vec3b hsvPixel = hsvImg.at<Vec3b>(y, x);
	printf("HSV color is [%d, %d, %d]\n", hsvPixel.val[0], hsvPixel.val[1],
			hsvPixel.val[2]);
	HSVThreshVals threshvals;
	getPixelThreshold((int)hsvPixel.val[0], (int)hsvPixel.val[1], (int)hsvPixel.val[2], &threshvals);
	return threshvals;
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
	printf("BGR color is [%d, %d, %d]\n", bgrPixel.val[0], bgrPixel.val[1],
			bgrPixel.val[2]);

	drawcolor[0] = (int)bgrPixel.val[0];
	drawcolor[1] = (int)bgrPixel.val[1];
	drawcolor[2] = (int)bgrPixel.val[2];

	cv::flip(imgHSV, imgHSVReflected, 1);
	HSVThreshVals threshvals = getHSVThreshold(imgHSVReflected, x, y);
	//cout << "HSV color is [" << hsvPixel.val[0] << "," << hsvPixel.val[1] << ","
	//		<< hsvPixel.val[2] << "]" << endl;
	/*
	printf("HSV color is [%d, %d, %d]\n", hsvPixel.val[0], hsvPixel.val[1],
			hsvPixel.val[2]);

	HSVThreshVals threshvals;
	getPixelThreshold((int)hsvPixel.val[0], (int)hsvPixel.val[1], (int)hsvPixel.val[2], &threshvals);
	*/

	printf("Setting threshold bounds H(%d,%d) S(%d,%d) V(%d,%d).\n",
			threshvals.LowH,
			threshvals.HighH,
			threshvals.LowS,
			threshvals.HighS,
			threshvals.LowV,
			threshvals.HighV);
	setThreshold(threshvals);
	//printfs alone were not giving output until the next cout was reached
	cout << "force out?" << endl;
}


static void threshold(Mat img, HSVThreshVals threshVals, Mat& out){
	inRange(img, Scalar(threshVals.LowH, threshVals.LowS, threshVals.LowV),
					Scalar(threshVals.HighH, threshVals.HighS, threshVals.HighV), out);
}


int colorchoose(int argc, char** argv) {

	VideoCapture cap = openCamera(0);

	createWindow("Ctrl");
	createWindow("Reflected");
	setMouseCallback("Reflected", onMouse, 0);

	addHSVThresholdBars("Ctrl", &iThreshVals);

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
		threshold(imgHSV, iThreshVals, imgThresholded);
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
						Scalar(drawcolor[0], drawcolor[1], drawcolor[2]), 2);
			}

			iLastX = posX;
			iLastY = posY;
		}


		Mat imgThresholdedReflected;
		cv::flip(imgThresholded, imgThresholdedReflected, 1);
		imshow("Thresholded + Reflected Image", imgThresholdedReflected); //show the thresholded image
		//imgOriginal = imgOriginal / 3;
		imgOriginal = imgOriginal + imgLines;
		//imshow("Original", imgOriginal); //show the original image

		cv::flip(imgOriginal, imgReflected, 1);
		imshow("Reflected", imgReflected); //show the reflected image
		int keypress = waitKey(1);
		if ( keypress == ASCII_CODE_ESCAPE ) //wait for 'esc' key press for 5ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user, quitting." << endl;
			break;
		}
		else if( keypress == ASCII_CODE_A_KEY ){
			cout << "a key is pressed by user, clearing tracklines." << endl;
			imgLines = getBlankFromCam(cap);
		}
	}

	return 0;
}
