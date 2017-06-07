#pragma once
#include "PlayMenu.h"

extern cv::Mat frame;
extern int width;
extern int height;
extern int xPos;
extern int yPos;
extern float rotationX;
extern float rotationY;
extern float rotationZ;
extern bool canRotate;
extern int level;
extern int points;
extern int totalPoints;
extern bool isFilled[20];
extern int shape;

class Main
{
public:
	static void BindCVMat2GLTexture(cv::Mat& image);
	static void drawFillTexture();
	static void drawWireframe();
};