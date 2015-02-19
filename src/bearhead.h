/*
 * bearhead.h
 *
 *  Created on: Nov 11, 2014
 *      Author: Ben
 */

#ifndef BEARHEAD_H_
#define BEARHEAD_H_

#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>


int colorchoose(int argc, char** argv);
int featuredetect(int argc, char** argv, std::vector<cv::KeyPoint>& blobpoint1, std::vector<cv::KeyPoint>& blobpoint2, bool inverse = false);
int featuredetect_essential(cv::Mat img_1, cv::Mat img_2, std::vector<cv::KeyPoint>& blobpoint1,
		std::vector<cv::KeyPoint>& blobpoint2, bool inverse = false);

int greendetect(int argc, char** argv);
int kalmanrob(int argc, char** argv);
int tracking(int argc, char** argv);
int unworked_triag(int argc, char** argv);
int twocams(int argc, char *argv[], char *window_name);
int twostreams(int argc, char** argv) ;
void loadImages(int argc, char** argv, cv::Mat* img1, cv::Mat* img2);
int triangulateTwoPoints(int argc, char** argv);


int sample_SBM( int argc, char** argv );
int sample_calibration(int argc, char* argv[]);
int sample_stereo_calibration(int argc, char** argv);

cv::VideoCapture openCamera(int num);
void createWindow(std::string window_name);
cv::Mat getBlankFromCam(cv::VideoCapture cam) ;
bool readFrame(cv::VideoCapture cam, cv::Mat* frame);

int ensurePositive(int val);
int ensureCapped(int val, int cap);


#endif /* BEARHEAD_H_ */
