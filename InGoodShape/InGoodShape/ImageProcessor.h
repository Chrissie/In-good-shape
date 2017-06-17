#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

class ImageProcessor
{
public:
	static void processImages();
	static void startImageThread();
};