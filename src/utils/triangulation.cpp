#include <iostream>
#include <stdio.h>
#include "../bearhead.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

vector<KeyPoint> pointything1, pointything2;


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

	/*float projMat[3][4] = { 6.5746697810243404e+002, 0., 3.1950000000000000e+002,0.,
		                                 0.,6.5746697810243404e+002, 2.3950000000000000e+002,0.,
		                                 0., 0., 1.,0.
		                                 };
*/
	float projMat[3][4] = { 0.878, -0.01 ,  0.479, -1.995,
			 0.01 ,  1.   ,  0.002, -0.226,
			-0.479,  0.002,  0.878,  0.615,
			 };
	Mat fakeProj = Mat(3,4, CV_32F ,projMat);
	fakeProj.convertTo(fakeProj, CV_64FC3);


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


	points1.convertTo(points1, CV_64FC2);
	points2.convertTo(points2, CV_64FC2);

	cout << points1 << endl;


	cout<< fakeProj <<endl;

	Mat triPoints = Mat(1,pointything1.size(),CV_64FC4,0);

	triangulatePoints(fakeProj, fakeProj, points1, points2, triPoints);

	cout << triPoints<<endl;

	return 0;
}



