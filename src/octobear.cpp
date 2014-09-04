#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
  Mat im = imread(argc == 2 ? argv[1] : "lenna.png", 1);
  if (im.empty())
  {
    cout << "Cannot open image!" << endl;
    return -1;
  }
  imshow("image", im);
  waitKey(0);
  return 0;
}
