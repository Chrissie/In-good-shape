#pragma once
#include "PlayMenu.h"
#include "MainMenu.h"
#include "OptionMenu.h"

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
extern int volume;
enum MenuState { MAIN, INSTRUCTIONS, START, OPTIONS, _EXIT };
extern MenuState menuState;
extern MainMenu* mainMenu;
extern PlayMenu* playScreen;
extern OptionMenu* optionMenu;
extern bool levelComplete;
extern int filledPercentage;
extern int oldFilledPercentage;
extern int area;

class Main
{
public:
	static void BindCVMat2GLTexture(cv::Mat& image);
	static void drawFillTexture();
	static void drawWireframe();
	static void switchMenu();
};