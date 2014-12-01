/*
 * Framing credit to Shermal Fernando
 * http://opencv-srf.blogspot.com/2010/09/object-detection-using-color-seperation.html
 *
 */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

void putPointIn1DMat(Mat m, int index, int px, int py){
	m.at<Vec2d>(0, index)[0] = px;
	m.at<Vec2d>(0, index)[1] = py;
}

int unworked_triag(int argc, char** argv) {
	//[ 6.5746697810243404e+002, 0., 3.1950000000000000e+002, 0.,
	//       6.5746697810243404e+002, 2.3950000000000000e+002, 0., 0., 1. ]
	// actual data pulled from one run of camera_calibration
	float calib_arr1[3][4] = { { 6.5746697810243404e+002, 0.,
			3.1950000000000000e+002, 0 }, { 0., 6.5746697810243404e+002,
			2.3950000000000000e+002, 0 }, { 0., 0., 1., 0 } };

	// this one is BS
	float calib_arr2[3][4] = { { 3.5746697810243404e+002, 0.,
			1.1950000000000000e+002, 0 }, { 0., 2.5746697810243404e+002,
			1.3950000000000000e+002, 0 }, { 0., 0., 1., 0 } };

	Mat camera1 = Mat(3, 4, CV_32F, calib_arr1);
	Mat camera2 = Mat(3, 4, CV_32F, calib_arr2);
	cout << "\nCam 1 matrix: \n" << camera1 << endl;
	cout << "\nCam 2 matrix: \n" << camera2 << endl;

	cout << "\n----------\n" << endl;

	int num_pts = 2;
	Mat pts3d = Mat(1, num_pts, CV_64FC4);

	Mat cam1pts = Mat(1, num_pts, CV_64FC2);
	putPointIn1DMat(cam1pts, 0, 150, 100);
	putPointIn1DMat(cam1pts, 1, 300, 200);
	Mat cam2pts = Mat(1, num_pts, CV_64FC2);
	putPointIn1DMat(cam2pts, 0, 200, 110);
	putPointIn1DMat(cam2pts, 1, 370, 230);
	cout << "Every two numbers is a point x and y.\n" << endl;
	cout << "Cam 1 pts: \n" << cam1pts << endl;
	cout << "Cam 2 pts: \n" << cam2pts << endl;

	triangulatePoints(camera1, camera2, cam1pts, cam2pts, pts3d);

	cout << "\n hold your breath \n ---------- \n" << endl;
	cout << "Triangulated 3D pts: \n" << pts3d << endl;

	return 0;
}
