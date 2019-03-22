#include<opencv2/opencv.hpp>
#include<stdint.h>

using namespace cv;
using namespace std;

const int fps = 60;

int main(int argv, char** argc)
{
	// Object to keep the video
	Mat frame;

	// Webcam
	VideoCapture vid(0);

	// If failed to open vid, exit program
	if (!vid.isOpened())
	{
		return -1;
	}

	while (vid.read(frame))
	{
		// Show video feed
		imshow("Webcam", frame);

		// If a key is pressed, the application will close
		if (waitKey(1000 / fps) >= 0)
			break;
	}

	return 1;

}