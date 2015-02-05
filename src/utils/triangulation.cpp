#include <iostream>
#include <stdio.h>
#include "../bearhead.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

vector<KeyPoint> pointything1, pointything2;
Mat triPoints;

int triangulateTwoPoints(int argc, char** argv){

	if (argc != 3) {
		//errar
		return -1;
	}

	Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

	featuredetect_essential(img_1, img_2, pointything1, pointything2, false);

	cout << "The x place thing is: \n" <<	pointything1[0].pt << pointything2[0].pt << endl;


	Mat fakeProj(2,2, CV_32F,1);

	//CvMat cvProj = fakeProj;


	cout << "row == " << fakeProj.rows << endl;

	triangulatePoints(fakeProj, fakeProj, pointything1, pointything2, triPoints);


	return 0;
}



