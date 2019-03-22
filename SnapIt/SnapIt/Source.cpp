#include<opencv2/opencv.hpp>
#include<stdint.h>
#include<string>
#include<iostream>
#include<cmath>
#include<Engine.h> // Connects to MATLAB

// I have no idea what this does, but it seems to be obligatory
#pragma comment (lib, "libmat.lib")
#pragma comment (lib, "libmx.lib")
#pragma comment (lib, "libmex.lib")
#pragma comment (lib, "libeng.lib")


using namespace cv;
using namespace std;



const int fps = 20;

int main(int argv, char** argc)
{

	Mat frame;				// Object to keep the video
	VideoCapture vid(0);	// Webcam

	// If failed to open vid, exit program
	if (!vid.isOpened())
	{
		return -1;
	}

	while (vid.read(frame))
	{
		// Show video feed
		imshow("Webcam, press Esc to close", frame);


		// Press s to capture the video frame
		if (waitKey(1000 / fps) == 's')
		{
			Mat frame2;				// Frame for the image we are going to capture
			frame2 = frame.clone();	// Cloning the image from the live feed
			imshow("Captured frame", frame2);
		}


		// If Esc key is pressed, the application will close
		if (waitKey(1000 / fps) == 27)
			break;
	}

	return 1;

}