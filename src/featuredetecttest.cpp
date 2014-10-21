#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

void readme();

/** @function main */
int main(int argc, char** argv) {
	if( argc != 3 )
	{ readme(); return -1; }

	Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE );
	Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE );

	if (!img_1.data || !img_2.data) {
		std::cout << " --(!) Error reading images " << std::endl;
		return -1;
	}

	//-- Step 1: Detect the keypoints
	// set up the parameters (check the defaults in opencv's code in blobdetector.cpp)
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 20.0f;
	params.maxArea = 500.0f;
	// ... any other params you don't want default value

	// set up and create the detector using the parameters
	cv::Ptr<cv::FeatureDetector> blob_detector = new cv::SimpleBlobDetector(
			params);
	blob_detector->create("SimpleBlob");

	// detect!

	std::vector<KeyPoint> keypoints_1, keypoints_2;

	cout << "good" << endl;

	blob_detector->detect(img_1, keypoints_1);
	cout << "good" << endl;

	blob_detector->detect(img_2, keypoints_2);
	cout << "good" << endl;

	//-- Draw keypoints
	Mat img_keypoints_1;
	Mat img_keypoints_2;

	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	cout << "good" << endl;

	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);
	cout << "good" << endl;

	waitKey(0);

	return 0;
}

/** @function readme */
void readme() {
	std::cout << " Usage: ./wjatever_detector <img1> <img2>" << std::endl;
}
