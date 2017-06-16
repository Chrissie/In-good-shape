#include "ImageProcessor.h"

int thres = 15;
int tempThres = 190;
int key;

Mat createBwImage(Mat image)
{
	Mat grey;
	cvtColor(image, grey, CV_BGR2GRAY);
	return grey;
}

Mat createThresholdImage(Mat image)
{
	Mat thresholdImg;
	threshold(image, thresholdImg, thres, 1, CV_THRESH_BINARY_INV);
	return thresholdImg;
}

void ImageProcessor::processImages(cv::Mat objectView, cv::Mat cameraView)
{
	Mat object = objectView;
	Mat camera = cameraView;
	double dWidth = object.cols;
	double dHeight = object.rows;

	Mat imageToCount;

	imshow("Frame1", object);
	imshow("Frame2", camera);
	
	tempThres = thres;
	thres = 190;

	cout << "\r\n counting objects...";
	imageToCount = createThresholdImage(createBwImage(object));

	Mat binary16S;
	imageToCount.convertTo(binary16S, CV_16S);
	Mat labelImg;

	vector<Point2d*> firstpixelvec;
	vector<Point2d*> pointvec;
	vector<int> areavec;

	int x = labelBLOBsInfo(binary16S, labelImg, firstpixelvec, pointvec, areavec);

	int totalarea = 0;
	for (vector<int>::iterator it = areavec.begin(); it != areavec.end(); ++it)
	{
		totalarea += *it;
	}

	//
	//Now the area for the BLOB objects is calculated
	//

	firstpixelvec.clear();
	pointvec.clear();
	areavec.clear();

	thres = tempThres;

	cout << "\r\n counting objects...";
	imageToCount = createThresholdImage(createBwImage(object));

	imageToCount.convertTo(binary16S, CV_16S);
	int count = 0;

	count = labelBLOBsInfo(binary16S, labelImg, firstpixelvec, pointvec, areavec);

	int totalareaobjects = 0;
	for (vector<int>::iterator it = areavec.begin(); it != areavec.end(); ++it)
	{
		totalareaobjects += *it;
	}

	cout << "\r\n counted " << count << " objects";
	cout << "\r\n area of camera: " << totalarea << endl;
	cout << "\r\n area of objects: " << totalareaobjects << endl;
	cout << "\r\n that is: " << (double)totalareaobjects / (double)totalarea * 100.0 << "%";
}
