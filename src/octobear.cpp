
// rawr bearhz

#include "bearhead.h"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

Mat img1, img2, img3, img4;


vector<KeyPoint> point1,point2;


int main( int argc, char** argv ){
	//loadImages(argc, argv, &img1, &img2);
	//kalmanrob(argc, argv);

	//sample_SBM(argc, argv);
	//sample_calibration(argc, argv);
	//string args[2] = {"sc1.jpg", "sc2.jpg"};

	//featuredetect(argc, argv);
	//unworked_triag(argc, argv);

	triangulateTwoPoints(argc, argv);

	//unworked_triag(argc, argv);


	//sample_stereo_calibration(argc, argv);

}
