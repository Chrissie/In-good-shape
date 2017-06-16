#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>
#include "blobdetectionavans.h"

using namespace cv;
using namespace std;

class ImageProcessor
{
public:
	void processImages(cv::Mat objectView, cv::Mat cameraView);
};