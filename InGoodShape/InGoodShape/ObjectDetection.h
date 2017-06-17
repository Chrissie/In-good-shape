#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>

using namespace std;
using namespace cv;

static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);

void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);

int objectDetectTest();