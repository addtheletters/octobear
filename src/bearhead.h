/*
 * bearhead.h
 *
 *  Created on: Nov 11, 2014
 *      Author: Ben
 */

#ifndef BEARHEAD_H_
#define BEARHEAD_H_

#include "opencv/cv.h"


int colorchoose(int argc, char** argv);
int featuredetect(int argc, char** argv);
int greendetect(int argc, char** argv);
int kalmanrob(int argc, char** argv);
int tracking(int argc, char** argv);
int unworked_triag(int argc, char** argv);
int twocams(int argc, char *argv[], char *window_name);
int twostreams(int argc, char** argv) ;
void loadImages(int argc, char** argv, cv::Mat* img1, cv::Mat* img2);


int sample_SBM( int argc, char** argv );
int sample_calibration(int argc, char* argv[]);
int sample_stereo_calibration(int argc, char** argv);

#endif /* BEARHEAD_H_ */
