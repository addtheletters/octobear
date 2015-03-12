#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/nonfree/nonfree.hpp"

using namespace cv;
using namespace std;

void readme_fdt();

/** @function main */
int featuredetect(int argc, char** argv, vector<KeyPoint>& blobpoint1,
		vector<KeyPoint>& blobpoint2, bool inverse = false) {
	if (argc != 3) {
		readme_fdt();
		return -1;
	}

	Mat img_1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

	if (inverse) {
		bitwise_not(img_1, img_1);
		bitwise_not(img_2, img_2);
		cout << "inverting grayscale image" << endl;
	}
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
	params.maxArea = 5000.0f;

	// ... any other params you don't want default value

	// set up and create the detector using the parameters
	Ptr<FeatureDetector> blob_detector = new SimpleBlobDetector(params);
	blob_detector->create("SimpleBlob");

	// detect!

	vector<KeyPoint> keypoints_1, keypoints_2;

	cout << "good" << endl;

	blob_detector->detect(img_1, keypoints_1);
	//cout << "KPs 1:\n" << Mat(keypoints_1) << endl;

	blob_detector->detect(img_2, keypoints_2);
	//cout << "KPs 2:\n" << Mat(keypoints_2) << endl;

	//-- Draw keypoints
	Mat img_keypoints_1;
	Mat img_keypoints_2;

	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	cout << "good?" << endl;

	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	imshow("Keypoints 2", img_keypoints_2);
	cout << "good" << endl;

	blobpoint1 = keypoints_1;
	blobpoint2 = keypoints_2;

	cout << "The featuredetect is done!\n" << endl;
	waitKey(0);

	return 0;
}

void createBlobDetector(Ptr<FeatureDetector> blob_detector){
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	/*params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	*/
	params.filterByArea = true;
	params.minArea = 20.0f;
	params.maxArea = 5000.0f;

	blob_detector = new SimpleBlobDetector(params);
	blob_detector->create("SimpleBlob");
}

int fdt(Mat img, Ptr<FeatureDetector> detector, vector<KeyPoint>& output){
	detector->detect(img, output);
}

int featuredetect_david(Mat img, vector<KeyPoint>& blobpoint1, bool inverse = false) {

	if (inverse) {
		bitwise_not(img, img);
		cout << "inverting grayscale image" << endl;
	}
	if (!img.data) {
		std::cout << " --(!) Error reading image " << std::endl;
		return -1;
	}

	//-- Step 1: Detect the keypoints
	// set up the parameters (check the defaults in opencv's code in blobdetector.cpp)
	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	/*params.filterByInertia = false;
	params.filterByConvexity = false;
	params.filterByColor = false;
	params.filterByCircularity = false;
	*/
	params.filterByArea = true;
	params.minArea = 20.0f;
	params.maxArea = 5000.0f;

	Ptr<FeatureDetector> blob_detector = new SimpleBlobDetector(params);
	blob_detector->create("SimpleBlob");

	vector<KeyPoint> keypoints_1;

	blob_detector->detect(img, keypoints_1);

	//-- Draw keypoints

	Mat img_keypoints_1;

	drawKeypoints(img, keypoints_1, img_keypoints_1, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	cout << "good?" << endl;

	//-- Show detected (drawn) keypoints
	imshow("Keypoints 1", img_keypoints_1);
	cout << "good" << endl;

	blobpoint1 = keypoints_1;
	return 0;
}


/*
 * img_1 and 2 grayscale image
 *
 */
int featuredetect_essential(Mat img_1, Mat img_2, vector<KeyPoint>& blobpoint1,
		vector<KeyPoint>& blobpoint2, bool inverse = false) {

	if (inverse) {
		bitwise_not(img_1, img_1);
		bitwise_not(img_2, img_2);
		cout << "inverting grayscale image" << endl;
	}

	if (!img_1.data || !img_2.data) {
		std::cout << " --(!) Error reading images " << std::endl;
		return -1;
	}

	cv::SimpleBlobDetector::Params params;
	params.minDistBetweenBlobs = 50.0f;
	//params.filterByInertia = false;
	//params.filterByConvexity = false;
	//params.filterByColor = false;
	//params.filterByCircularity = false;
	params.filterByArea = true;
	params.minArea = 20.0f;
	params.maxArea = 5000.0f;
	Ptr<FeatureDetector> blob_detector = new SimpleBlobDetector(params);
	blob_detector->create("SimpleBlob");

	vector<KeyPoint> keypoints_1, keypoints_2;
	blob_detector->detect(img_1, keypoints_1);
	blob_detector->detect(img_2, keypoints_2);

	//-- Draw keypoints
	Mat img_keypoints_1;
	Mat img_keypoints_2;
	drawKeypoints(img_1, keypoints_1, img_keypoints_1, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	drawKeypoints(img_2, keypoints_2, img_keypoints_2, Scalar::all(-1),
			DrawMatchesFlags::DEFAULT);
	// return
	//cout << "Poop" << keypoints_1[0].pt << keypoints_2[0].pt << endl;
	blobpoint1 = keypoints_1;
	blobpoint2 = keypoints_2;
	return 0;
}

/** @function readme */
void readme_fdt() {
	std::cout << " Usage: ./wjatever_detector <img1> <img2>" << std::endl;
}
