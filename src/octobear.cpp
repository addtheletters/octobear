#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

char key;
int main_no() {
	cvNamedWindow("Camera_Output", 1);    //Create window
	CvCapture* capture = cvCaptureFromCAM(CV_CAP_ANY); //Capture using any camera connected to your system
	while (1) { //Create infinte loop for live streaming

		Mat* frame = (Mat*) (cvQueryFrame(capture)); //Create image frames from capture
		Mat out;
		GaussianBlur( *frame , out, Size(11, 11), 1.5 );

		cvShowImage("Camera_Output", &out); //Show image frames on created window

		key = cvWaitKey(1);     //Capture Keyboard stroke
		if (char(key) == 27) {
			break;      //If you hit ESC key loop will break.
		}
	}
	cvReleaseCapture(&capture); //Release capture.
	cvDestroyWindow("Camera_Output"); //Destroy Window
	return 0;
}

/*
 int main_alt( int argc, char** argv )
 {
 if( argc != 2)
 {
 cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
 return -1;
 }

 Mat image;
 image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

 if(! image.data )                              // Check for invalid input
 {
 cout <<  "Could not open or find the image" << std::endl ;
 return -1;
 }

 namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
 imshow( "Display window", image );                   // Show our image inside it.

 waitKey(0);                                          // Wait for a keystroke in the window
 return 0;
 }
 */
