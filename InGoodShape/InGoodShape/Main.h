#pragma once

extern cv::Mat frame;

class Main
{
public:
	static void BindCVMat2GLTexture(cv::Mat& image);

};