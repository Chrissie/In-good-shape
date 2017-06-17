#include "MenuComponent.h"
#include <GL/glew.h>
#include "blobdetectionavans.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "Main.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "PyramidComponent.h"
#include "HouseComponent.h"


cv::Mat frame;

GameObject* scoreObject;
GameObject* levelObject;
GameObject* totalScoreObject;
GameObject* percentageObject;

float middleX, middleY;
int currentLevel;

PlayMenu::PlayMenu()
{
	
	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("IN GOOD SHAPE"));
	title->position = ::Vec3f(-400, 4, 0);
	objects.push_back(title);

	levelObject = new GameObject();
	levelObject->addComponent(new MenuComponent("Level: " + std::to_string(level), 0.5));
	levelObject->position = ::Vec3f(860, 5, 0);
	objects.push_back(levelObject);

	scoreObject = new GameObject();
	scoreObject->addComponent(new MenuComponent("Score: " + std::to_string(points), 0.5));
	scoreObject->position = ::Vec3f(860, 4.5, 0);
	objects.push_back(scoreObject);

	totalScoreObject = new GameObject();
	totalScoreObject->addComponent(new MenuComponent("Total score: " + std::to_string(totalPoints), 0.5));
	totalScoreObject->position = ::Vec3f(860, 4, 0);
	objects.push_back(totalScoreObject);

	percentageObject = new GameObject();
	percentageObject->addComponent(new MenuComponent("Filled:" + std::to_string(oldFilledPercentage) + "%", 0.5));
	percentageObject->position = ::Vec3f(860, 3.5, 0);
	objects.push_back(percentageObject);

	currentLevel = level;
	switchLevel();
}


PlayMenu::~PlayMenu()
{
}

void PlayMenu::switchLevel()
{
	if(level == 1)
	{
		GameObject* cube = new GameObject();
		cube->addComponent(new CubeComponent(1.5));
		cube->position = ::Vec3f(0, -1, 0);
		objects.push_back(cube);
	}
	if(level == 2)
	{
		objects.pop_back();
		GameObject* pyramid = new GameObject();
		pyramid->addComponent(new PyramidComponent(2, 3));
		pyramid->position = ::Vec3f(0, -0.7, 0);
		objects.push_back(pyramid);
	}
	if(level == 3)
	{
		objects.pop_back();
		GameObject* house = new GameObject();
		house->addComponent(new HouseComponent(1.5, 1.5, 2.5));
		house->position = ::Vec3f(0, -0.5, 0);
		objects.push_back(house);
	}

}


void PlayMenu::update()
{
	if(scoreObject->getComponent<MenuComponent>() != nullptr)
		scoreObject->getComponent<MenuComponent>()->title = "Score: " + to_string(points);
	if (levelObject->getComponent<MenuComponent>() != nullptr)
		levelObject->getComponent<MenuComponent>()->title = "Level: " + to_string(level);
	if (totalScoreObject->getComponent<MenuComponent>() != nullptr)
		totalScoreObject->getComponent<MenuComponent>()->title = "Total score: " + to_string(totalPoints);
	if (percentageObject->getComponent<MenuComponent>() != nullptr)
		percentageObject->getComponent<MenuComponent>()->title = "Filled:" + std::to_string(oldFilledPercentage) + "%";

	if(currentLevel != level)
	{
		currentLevel = level;
		switchLevel();
	}
}

void PlayMenu::draw()
{
	//for (auto &o : gameModel)
	//{
	//	glPushMatrix();
	//	glTranslatef(0, 0, 0);
	//	o->draw();
	//	glPopMatrix();
	//}



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

	Main::BindCVMat2GLTexture(frame);
	glEnable(GL_TEXTURE_2D);
	glUseProgram(0);

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/

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