#include "PlayMenu.h"
#include "MenuComponent.h"
#include <GL/glew.h>
#include "blobdetectionavans.h"
#include "Main.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "PyramidComponent.h"

cv::Mat frame;



PlayMenu::PlayMenu()
{
	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("Play the game !!!"));
	title->position = ::Vec3f(-400, 4, 0);
	objects.push_back(title);

	GameObject* cube = new GameObject();
	cube->addComponent(new CubeComponent(1));
	cube->position = ::Vec3f(0, -2, 0);
	objects.push_back(cube);

	/*GameObject* pyramid = new GameObject();
	pyramid->addComponent(new PyramidComponent(1, 1.5));
	pyramid->position = ::Vec3f(0, 0, 0);
	objects.push_back(pyramid);*/
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

void PlayMenu::drawCameraWithOverlay()
{
	Main::BindCVMat2GLTexture(frame);
	glEnable(GL_TEXTURE_2D);
	glUseProgram(0);

	glPushMatrix();
	glTranslatef(-8, -6, -1.45);
	glScaled(16, 12, 0);
	glAlphaFunc(GL_LESS, 0.5);
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, 1.0, 0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 0.0, 0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 1.0, 0);
	glEnd();
	glPopMatrix();
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

	Main::BindCVMat2GLTexture(frame);
	glEnable(GL_TEXTURE_2D);
	glUseProgram(0);

	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(0, 1, 0, 1, -10, 10);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	//front
	
	glColor4f(1, 1, 1, 1);
	glPushMatrix();
	glTranslatef(-8, -6, -1.5);
	glScaled(16, 12, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0, 1.0, 0);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0, 0.0, 0);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.0, 0.0, 0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.0, 1.0, 0);
	glEnd();
	glPopMatrix();
}