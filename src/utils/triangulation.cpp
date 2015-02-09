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

	cout << "The x place thing is: " <<	pointything1[0].pt << pointything2[0].pt << endl;

	cout <<typeid(pointything1[0].pt.x).name() << endl;

	Mat fakeProj(3,4, CV_32F ,1);



	//CvMat cvProj = fakeProj;

	Mat points1(2,pointything1.size(),CV_32F);

	Mat points2(2,pointything1.size(),CV_32F);

	for (int i =0; i < pointything1.size(); i++){
		points1.at<float>(0,i)=pointything1[i].pt.x;
		points1.at<float>(1,i)=pointything1[i].pt.y;
	}

	for (int i =0; i < pointything2.size(); i++){
			points2.at<float>(0,i)=pointything2[i].pt.x;
			points2.at<float>(1,i)=pointything2[i].pt.y;
		}



	cout << points1 << endl;

	triangulatePoints(fakeProj, fakeProj, points1, points2, triPoints);

	cout << triPoints<<endl;

	return 0;
}



