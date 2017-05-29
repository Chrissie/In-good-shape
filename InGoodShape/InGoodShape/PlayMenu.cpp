#include "PlayMenu.h"
#include "MenuComponent.h"
#include <GL/glew.h>
#include "blobdetectionavans.h"
#include "Main.h"
#include <opencv2/imgproc/imgproc.hpp>

cv::Mat frame;



PlayMenu::PlayMenu()
{
	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("Play the game!"));
	title->position = ::Vec3f(-400, 4, 0);
	objects.push_back(title);
}


PlayMenu::~PlayMenu()
{
}

void PlayMenu::update()
{
	
}

void PlayMenu::draw()
{
	drawCamera();
}



void PlayMenu::drawCamera()
{
	//Mat black(frame.rows, frame.cols, frame.type(), cv::Scalar::all(0));
	//Mat mask(frame.rows, frame.cols, CV_8UC1, cv::Scalar(0));

	//vector< vector<Point> >  co_ordinates;
	//co_ordinates.push_back(vector<Point>());
	//co_ordinates[0].push_back(Point(1,1));
	//co_ordinates[0].push_back(Point(10,1));
	//co_ordinates[0].push_back(Point(10,10));
	//co_ordinates[0].push_back(Point(1,10));
	//drawContours(mask, co_ordinates, -1, Scalar(255), CV_FILLED, 8);

	//black.copyTo(frame, mask);

	glEnable(GL_TEXTURE_2D);
	Main::BindCVMat2GLTexture(frame);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex2f(50, 50);
	//glTexCoord2f(1.0f, 1.0f);
	//glVertex2f(1600, 50);
	//glTexCoord2f(1.0f, 0.0f);
	//glVertex2f(1600, 1000);
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex2f(50, 1000);

	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1000, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1000, 1000, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1000, 0, 0);

	glEnd();

	imshow("hello Duc", frame);
}