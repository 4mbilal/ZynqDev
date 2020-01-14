#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "iostream"
using namespace cv;
using namespace std;
int main( )
{
  Mat frame, gray;
  //image = imread("shape.jpg", 1);  
  namedWindow( "Processed Frame", CV_WINDOW_AUTOSIZE );  
  VideoCapture cap(0);

  while(1){
   cap>>frame;
    
   cvtColor(frame, gray, CV_BGR2GRAY);
   Canny(gray, gray, 100, 200, 3);
   /// Find contours   
   /*vector<vector<Point> > contours;
   vector<Vec4i> hierarchy;
   RNG rng(12345);
   findContours( gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
   /// Draw contours
   Mat drawing = Mat::zeros( gray.size(), CV_8UC3 );
   for( int i = 0; i< contours.size(); i++ )
   {
     Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
     drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     } */    
 
   imshow("Processed Frame",gray);
   waitKey(1);
  }
   return 0;
}
