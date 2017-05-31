#pragma once

extern cv::Mat frame;
extern int width;
extern int height;
extern int xPos;
extern int yPos;

class Main
{
public:
	static void BindCVMat2GLTexture(cv::Mat& image);

};