
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

void putPointIn1DMat(Mat m, int index, int px, int py){
	m.at<Vec2d>(0, index)[0] = px;
	m.at<Vec2d>(0, index)[1] = py;
}

Mat_<double> LinearLSTriangulation(Point3d u,   	//homogenous image point (u,v,1)
                   Matx34d P,   	//camera 1 matrix
                   Point3d u1,  	//homogenous image point in 2nd camera
                   Matx34d P1   	//camera 2 matrix
                                   )
{
    //build matrix A for homogenous equation system Ax = 0
    //assume X = (x,y,z,1), for Linear-LS method
    //which turns it into a AX = B system, where A is 4x3, X is 3x1 and B is 4x1
    Matx43d A(u.x*P(2,0)-P(0,0),	u.x*P(2,1)-P(0,1),  	u.x*P(2,2)-P(0,2),
          u.y*P(2,0)-P(1,0),	u.y*P(2,1)-P(1,1),  	u.y*P(2,2)-P(1,2),
          u1.x*P1(2,0)-P1(0,0), u1.x*P1(2,1)-P1(0,1),   u1.x*P1(2,2)-P1(0,2),
          u1.y*P1(2,0)-P1(1,0), u1.y*P1(2,1)-P1(1,1),   u1.y*P1(2,2)-P1(1,2)
              );
    Matx41d B(	-(u.x*P(2,3)	-P(0,3)),
                      -(u.y*P(2,3)  -P(1,3)),
                      -(u1.x*P1(2,3)	-P1(0,3)),
                      -(u1.y*P1(2,3)	-P1(1,3)));

    Mat_<double> X;
    solve(A,B,X,DECOMP_SVD);

    return X;
}


int unworked_triag(int argc, char** argv) {
	//[ 6.5746697810243404e+002, 0., 3.1950000000000000e+002, 0.,
	//       6.5746697810243404e+002, 2.3950000000000000e+002, 0., 0., 1. ]
	// actual data pulled from one run of camera_calibration
	float calib_arr1[3][4] = { { 6.5746697810243404e+002, 0.,
			3.1950000000000000e+002, 0 }, { 0., 6.5746697810243404e+002,
			2.3950000000000000e+002, 0 }, { 0., 0., 1., 0 } };

	// this one is BS
	float calib_arr2[3][4] = { { 6.5546697810243404e+002, 0.,
			3.1900000000000000e+002, 0 }, { 0., 6.5706697810243404e+002,
			2.3900000000000000e+002, 0 }, { 0., 0., 1., 0 } };

	Mat camera1 = Mat(3, 4, CV_32F, calib_arr1);
	Mat camera2 = Mat(3, 4, CV_32F, calib_arr2);
	cout << "\nCam 1 matrix: \n" << camera1 << endl;
	cout << "\nCam 2 matrix: \n" << camera2 << endl;

	cout << "\n----------\n" << endl;

	int num_pts = 2;
	Mat pts3d = Mat(1, num_pts, CV_64FC4);

	Mat cam1pts = Mat(1, num_pts, CV_64FC2);
	putPointIn1DMat(cam1pts, 0, 1, 1);
	putPointIn1DMat(cam1pts, 1, 1, 1);
	Mat cam2pts = Mat(1, num_pts, CV_64FC2);
	putPointIn1DMat(cam2pts, 0, 200, 110);
	putPointIn1DMat(cam2pts, 1, 370, 230);
	cout << "Every two numbers is a point x and y.\n" << endl;
	cout << "Cam 1 pts: \n" << cam1pts << endl;
	cout << "Cam 2 pts: \n" << cam2pts << endl;

	cout << "\n hold your breath \n ---------- \n" << endl;

	triangulatePoints(camera1, camera2, cam1pts, cam2pts, pts3d);

	cout << "Triangulated 3D pts: \n" << pts3d << endl;

	cout << "\n hold your breath again \n ---------- \n" << endl;

	Point3d one = Point3d(.1, .3, 1);
	Point3d two = Point3d(.5, .4, 1);

	//Mat_ um1 =

	Mat_<double> linear_sth = LinearLSTriangulation( one, camera1, two, camera2 );

	cout << "LinearLSTriangulation 3D pt: \n" << linear_sth << endl;

	return 0;
}


