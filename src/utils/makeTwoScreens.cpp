#include <iostream>
#include <stdio.h>
#include "../bearhead.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>


using namespace cv;
using namespace std;

void openTwoScreens(Mat* img1, Mat* img2) {

	while (true) {
		int key = cvWaitKey(5);


		imshow("Image1", *img1);
		imshow("Image2", *img2);

		if (key == 27) {
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}
}

void loadImages(int argc, char** argv, Mat* img1, Mat* img2) {
	printf("lol");
	Mat matt = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	Mat savage = imread(argv[2], CV_LOAD_IMAGE_COLOR);

	img1 = &matt;
	img2 = &savage;

	//featuredetect(argc, argv);

	openTwoScreens(img1, img2);
}

