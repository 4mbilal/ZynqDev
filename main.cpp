#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

#include "GPIOClass.h"
#include "VDMA.h"

#define VDMAWidth 752
#define VDMAHeight 480
#define VDMAPixelWidth 8
#define VDMAFB1Adr 0x1e000000
#define VDMAFB2Adr 0x1f000000
#define VDMABaseAddr 0x43000000

using namespace cv;
using namespace std;

int contour_example();
int WebCam_example();
int GPIO_example();

int main( )
{
//	contour_example();
//	WebCam_example();
//	GPIO_example();
	//vdma_test();
	vdma_mat_test();
}


int GPIO_example()
{
    GPIOClass* LD4 = new GPIOClass("61"); //GPIO7 + 54 Offset
    GPIOClass* LD5 = new GPIOClass("62"); //GPIO8 + 54 Offset
    GPIOClass* LD6 = new GPIOClass("63"); //GPIO9 + 54 Offset
    GPIOClass* LD7 = new GPIOClass("64"); //GPIO10 + 54 Offset
    GPIOClass* SW0 = new GPIOClass("65"); //GPIO11 + 54 Offset
    GPIOClass* SW1 = new GPIOClass("66"); //GPIO12 + 54 Offset
    GPIOClass* SW2 = new GPIOClass("67"); //GPIO13 + 54 Offset
    GPIOClass* SW3 = new GPIOClass("68"); //GPIO14 + 54 Offset
    GPIOClass* SW4 = new GPIOClass("69"); //GPIO15 + 54 Offset
    GPIOClass* SW5 = new GPIOClass("70"); //GPIO16 + 54 Offset
    GPIOClass* SW6 = new GPIOClass("71"); //GPIO17 + 54 Offset
    GPIOClass* SW7 = new GPIOClass("72"); //GPIO18 + 54 Offset

    LD4->export_gpio(); 
    LD5->export_gpio(); 
    LD6->export_gpio(); 
    LD7->export_gpio(); 
    SW0->export_gpio(); 
    SW1->export_gpio(); 
    SW2->export_gpio(); 
    SW3->export_gpio(); 
    SW4->export_gpio(); 
    SW5->export_gpio(); 
    SW6->export_gpio(); 
    SW7->export_gpio(); 

    cout << "GPIO pins exported" << endl;

    SW0->setdir_gpio("in");
    SW1->setdir_gpio("in");
    SW2->setdir_gpio("in");
    SW3->setdir_gpio("in");
    SW4->setdir_gpio("in");
    SW5->setdir_gpio("in");
    SW6->setdir_gpio("in");
    SW7->setdir_gpio("in");
    LD4->setdir_gpio("out");
    LD5->setdir_gpio("out");
    LD6->setdir_gpio("out");
    LD7->setdir_gpio("out");

    cout << "GPIO pin directions set!" << endl;

    string SWstate[8];
    while(1)
    {
        //usleep(500000);  // wait for 0.5 seconds
        SW0->getval_gpio(SWstate[0]); //read switch state
        SW1->getval_gpio(SWstate[1]); //read switch state
        SW2->getval_gpio(SWstate[2]); //read switch state
        SW3->getval_gpio(SWstate[3]); //read switch state
        SW4->getval_gpio(SWstate[4]); //read switch state
        SW5->getval_gpio(SWstate[5]); //read switch state
        SW6->getval_gpio(SWstate[6]); //read switch state
        SW7->getval_gpio(SWstate[7]); //read switch state
        cout << "Switches = " << SWstate[7] << SWstate[6] << SWstate[5] << SWstate[4] << SWstate[3] << SWstate[2] << SWstate[1] << SWstate[0]  <<endl;

        LD4->setval_gpio(SWstate[4]); // turn LED ON based on SW status
        LD5->setval_gpio(SWstate[5]); // turn LED ON based on SW status
        LD6->setval_gpio(SWstate[6]); // turn LED ON based on SW status
        LD7->setval_gpio(SWstate[7]); // turn LED ON based on SW status
    }

    cout << "Exiting....." << endl;
    return 0;	
}

int WebCam_example()
{
	VideoCapture  cap(0);
	if(!cap.isOpened())
		return -1;

	Mat edges;
	namedWindow("Edges",1);
	Mat frame;

	while(1)
	{
		cap>>frame;
		cvtColor(frame,edges,CV_BGR2GRAY);
		GaussianBlur(edges,edges,Size(7,7),1.5,1.5);
		Canny(edges,edges,0,30,3);
		imshow("Edges",edges);
		if(waitKey(30) >= 0) break;		
	}
	return 0;
}

int contour_example()
{
    Mat image;
    image = imread("shape.jpg", 1);  
    namedWindow( "Display window", CV_WINDOW_AUTOSIZE );  
    imshow( "Display window", image );
    Mat gray;
    cvtColor(image, gray, CV_BGR2GRAY);
    Canny(gray, gray, 100, 200, 3);
    /// Find contours   
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    findContours( gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
    /// Draw contours
    Mat drawing = Mat::zeros( gray.size(), CV_8UC3 );
    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
    }     
 
    imshow( "Result window", drawing );
    waitKey(0);                                         
    return 0;
}
