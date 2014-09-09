#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	VideoCapture cap(0); //capture the video from web cam
	VideoCapture cap1(1);
	VideoCapture cap2(2);

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
	}
	if (!cap1.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam (1)" << endl;
	}
	if (!cap2.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam (2)" << endl;
	}

	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 179;

	int iLowS = 0;
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);



	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true) {
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video

		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV),
				Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

		//morphological opening (remove small objects from the foreground)
		erode(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded,
				getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		Mat imgcam1;
		Mat imgcam2;

		bool b1Success = cap1.read(imgcam1); // read a new frame from video

		if (!b1Success) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream (1)" << endl;
			//break;
		}

		bool b2Success = cap2.read(imgcam2); // read a new frame from video

		if (!b2Success) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream (2)" << endl;
			//break;
		}

		if (bSuccess) {
			imshow("Thresholded Image (0)", imgThresholded); //show the thresholded image
			imshow("Original (0)", imgOriginal); //show the original image
		}
		if (b1Success) {
			Mat imgReflected;
			cv::flip(imgcam1, imgReflected, 1);
			imshow("Reflected (1)", imgReflected); //show the reflected image
		}
		if (b2Success) {
			imshow("Original (2)", imgcam2);
		}
		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	return 0;

}
