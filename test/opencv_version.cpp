#include "opencv2/core/core1.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
using namespace std;
using namespace cv;

int main()
{
  Mat frame;
  VideoCapture cap(0);
  while(1){
    cap>>frame;
    imshow("Frame",frame);
    waitKey(1);
  }

    return 0;
}
