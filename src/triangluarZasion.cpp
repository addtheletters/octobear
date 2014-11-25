/*
 * Framing credit to Shermal Fernando
 * http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int unworked_triag(int argc, char** argv) {
	//[ 6.5746697810243404e+002, 0., 3.1950000000000000e+002, 0.,
	//       6.5746697810243404e+002, 2.3950000000000000e+002, 0., 0., 1. ]
	// actual data pulled from one run of camera_calibration
	float calib_arr1[3][4] = {
			{ 6.5746697810243404e+002, 0., 3.1950000000000000e+002,	0 },
			{ 0., 6.5746697810243404e+002, 2.3950000000000000e+002,	0 },
			{ 0., 0., 1.,											0 }
	};

	// this one is BS
	float calib_arr2[3][4] = {
			{ 3.5746697810243404e+002, 0., 1.1950000000000000e+002,	0 },
			{ 0., 2.5746697810243404e+002, 1.3950000000000000e+002,	0 },
			{ 0., 0., 1.,											0 }
	};

	Mat camera1 = Mat(3, 4, CV_32F, calib_arr1);
	Mat camera2 = Mat(3, 4, CV_32F, calib_arr2);
	cout << "\nCam 1 matrix: \n" << camera1 << endl;
	cout << "\nCam 2 matrix: \n" << camera2 << endl;



	return 0;
}
