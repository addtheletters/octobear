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
	featuredetect(argc, argv, pointything1, pointything2, false);

	cout << "The x place thing is: \n" <<	pointything1.size() << endl;


	return 0;
}



