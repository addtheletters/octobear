
// rawr bearhz

#include "bearhead.h"
#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


using namespace cv;
using namespace std;

Mat img1, img2;

int main( int argc, char** argv ){
	loadImages("dot1.png", "dot2.png", &img1, &img2);
	kalmanrob(argc, argv);
}
