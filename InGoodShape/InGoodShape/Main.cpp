// Standard includes.
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// freeglut
#include <GL/freeglut.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

// openCV tools
#include "opencv2/imgproc/imgproc.hpp" 
#include "opencv2/highgui/highgui.hpp"
#include "blobdetectionavans.h"
#include "ObjectDetection.h"

// GL includes
#include "Main.h"
#include "Shader.h"
#include "GameObject.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MenuComponent.h"
#include "PyramidComponent.h"
#include "Menu.h"
#include "Text.h"
#include <chrono>
#include <vector>
#include <iterator>
#include "MainMenu.h"
#include "InstructionMenu.h"
#include "PlayMenu.h"
#include "OptionMenu.h"


//sound
#include "Sound.h"


int mouseX = 0;
int mouseY = 0;

//int width;
//int height;

float rotationX = 0;
float rotationY = 0;
float rotationZ = 0;
float deltaTime;
float mouseSpeedX = 0;
float mouseSpeedY = 0;

int xPos = 0;
int yPos = 0;

float oldX = 0;
float oldY = 0;

bool keys[256];

int lastTime = 0;

int width = 1920;
int height = 1080;

bool canRotate = true;

int level = 1;	//displays current level in PlayMenu
int points = 100;	//displays points in current level in PlayMenu
int totalPoints = 999;	//displays total points from all played levels in PlayMenu
bool isFilled[20];	// used to see which side of 3D object to fill
int shape = -1;		// used for object detection
int rotationspeed = 25; // used to rotate the gameObject in PlayMenu

std::list<GameObject*> objects;

Text* text;
Menu menu;
MainMenu* mainMenu;
InstructionMenu* instructionMenu;
PlayMenu* playScreen;
OptionMenu* optionMenu;

bool selectedButtons[10];

enum MenuState { MAIN, INSTRUCTIONS, START, OPTIONS, _EXIT } menuState;

// Prototype
void switchMenu();


cv::VideoCapture cap(0);
//cv::Mat frame;
GLuint *textures = new GLuint[1]{ 0 };

//returns true if init was succesful, else return false
bool cvInit()
{
	return cap.read(frame);
}

void Main::BindCVMat2GLTexture(cv::Mat& image)
{
	if (image.empty()) {
		std::cout << "image empty" << std::endl;
	}
	else 
	{
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		if(textures[0] == 0)
			glGenTextures(1, textures);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		//cv::cvtColor(image, image, CV_BGR2RGB);
		unsigned char* data = image.ptr();

		glTexImage2D(GL_TEXTURE_2D,         // Type of texture
			0,					 // Pyramid level (for mip-mapping) - 0 is the top level
			GL_RGB,              // Internal colour format to convert to
			image.cols,          // Image width  i.e. 640
			image.rows,          // Image height i.e. 480
			0,                   // Border width in pixels (can either be 1 or 0)
			GL_BGR,              // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,    // Image data type
			data);        // The actual image data itself

		glBindTexture(GL_TEXTURE_2D, textures[0]);
	}
}

void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	cout << key << endl;
	switch (key) {
	case 27: exit(0);
		break;
	case 32: toggleBackgroundMusic();
		break;
	case 'm': menuScrollSFX();
		break;
	default: //nothing
		break;
	}
	if (keys[key] == false)
	{
		keys[key] = true;

		if (keys['1'])
		{
			menu.selectButton(0);
			if (menuState == MAIN) menuState = INSTRUCTIONS;
			else if (menuState == INSTRUCTIONS) menuState = MAIN;
			else if (menuState == OPTIONS) menuState = MAIN;
		}
		if (keys['2'])
		{
			menu.selectButton(1);
			if (menuState == MAIN) menuState = START;
		}
		if (keys['3'])
		{
			menu.selectButton(2);
			if (menuState == MAIN) menuState = OPTIONS;
		}
		if (keys['4'])
		{
			menu.selectButton(3);
			if (menuState == MAIN) menuState = _EXIT;
		}
		if (keys[13]) //enter key
		{
			for (int i = 0; i < sizeof(selectedButtons); i++)
				selectedButtons[i] = false;
			switchMenu();
		}
		if (keys[32])
		{
			canRotate = !canRotate;
		}
			
	}
}

void keyboardUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}

void rotate(int x, int y)
{
	if (x < oldX )
	{
		if(rotationX > 150 && rotationX < 210 )
		{
			rotationY -= deltaTime * 180;
		} else
		{
			rotationY += deltaTime * 180;
		}
		
	}
	if (x > oldX)
	{ //+
		if (rotationX < -150 && rotationX > -210)
		{
			rotationY -= deltaTime * 180;
		}
		else
		{
			rotationY += deltaTime * 180;
		}
	}
	if (y < oldY)
	{
		rotationX -= deltaTime * 180;
	}
	if (y > oldY)
	{
		rotationX += deltaTime * 180;
	}
}

void mouseMotion(int x, int y)
{
	if(canRotate)
	{
		float deltaX = oldX - x;
		float deltaY = oldY - y;

		mouseSpeedX = (deltaX / deltaTime) / 100;
		mouseSpeedY = (deltaY / deltaTime) / 100;

		rotate(x, y);

		oldX = static_cast<float>(x);
		oldY = static_cast<float>(y);
	}
}

void moveCube(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT: xPos--;
		break;
	case GLUT_KEY_RIGHT: xPos++;
		break;
	case GLUT_KEY_UP: yPos++;
		break;
	case GLUT_KEY_DOWN: yPos--;
		break;
	default: //nothing
		break;
	}
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	menuState = MAIN;
	mainMenu = new MainMenu();
	instructionMenu = nullptr;
	playScreen = nullptr;
	optionMenu = nullptr;
	for (auto b : isFilled)
		b = false;
}

void drawCube()
{
	//front
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 1, 0);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, 0, 0);

	//back
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, -1);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1, -1);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, 0, -1);

	//left side
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, -1);

	//right side
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1, 0, -1);

	//bottom
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 0, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 0, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 0, -1);

	//top
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0, 1, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1, 1, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0, 1, -1);
	glEnd();
}

void Main::drawFillTexture()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Main::drawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}


void display()
{
	glUseProgram(0);	// Important to use the correct program ID.
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, width / (float)height, 0.1f, 50.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 5,
		0, 0, 0,
		0, 1, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[0]);


	int count = 0;
	for (auto &o : objects)
	{
		if (o->getComponent<SpinComponent>() != nullptr)
		{
			SpinComponent * spinComponent = o->getComponent<SpinComponent>();

			if (selectedButtons[count])
				spinComponent->spinAll();
			else
				spinComponent->stopSpin();
		}
		count++;



		if(playScreen != nullptr && o != objects.front() && o->getComponent<MenuComponent>() == nullptr)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
			

		o->draw();
	}



	//draw cube
	//glPushMatrix();
	//glTranslatef(xPos, yPos, 4);

	
	//draw cube
	//glPushMatrix();
	//glTranslatef(0, 0, 0);

	//glTranslatef(0.5, 0.5, -0.5);
	//glRotatef(rotationX, 1, 0, 0);
	//glRotatef(rotationY, 0, 1, 0);
	//glTranslatef(-0.5, -0.5, 0.5);

	//drawCube();
	//glPopMatrix();

	//text->RenderText("IN GOOD SHAPE", (width/8), height/1.2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	//glBindTexture(GL_TEXTURE_2D, textures[0]);


	if (playScreen)
		playScreen->draw();


	glutSwapBuffers();
}

void switchMenu()
{
	switch (menuState)
	{
	case MAIN: 
		if (mainMenu == nullptr)
		{
			delete instructionMenu; 
			delete optionMenu;
			instructionMenu = nullptr; 
			optionMenu = nullptr;
			mainMenu = new MainMenu();
		}
		break;
	case INSTRUCTIONS: 
		if (instructionMenu == nullptr)
		{
			delete mainMenu; 
			mainMenu = nullptr; 
			instructionMenu = new InstructionMenu();
		}
		break;
	case START:
		if(playScreen == nullptr)
		{
			delete mainMenu;
			mainMenu = nullptr;
			playScreen = new PlayMenu();
		}
		break;
	case OPTIONS:
		if(optionMenu == nullptr)
		{
			delete mainMenu;
			mainMenu = nullptr;
			optionMenu = new OptionMenu();
		}
		break;
	case _EXIT:
		exit(0);
		break;
	}
}
	

void idle()
{
	//int shape = objectDetectTest();
	switch(shape)
	{
	case 0: menu.selectButton(0); std::cout << "selected 1" << std::endl;
		break;
	case 1: menu.selectButton(1); cout << "selected 2" << endl;
		break;
	case 2: menu.selectButton(2); cout << "selected 3" << endl;
		break;
	case 3: menu.selectButton(3); cout << "selected 4" << endl;
		break;
	default: break;
	}

	if (cap.read(frame))
	{
		Main::BindCVMat2GLTexture(frame);
	}

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;
	if (canRotate)
	{
		if (keys['w'] || shape == 0)
		{
			rotationX -= deltaTime * rotationspeed;
		}
		if (keys['s'] || shape == 2)
		{
			rotationX += deltaTime * rotationspeed;
		}
		if (keys['a'] || shape == 3)
		{
			rotationY -= deltaTime * rotationspeed;
		}
		if (keys['d'] || shape == 1)
		{
			rotationY += deltaTime * rotationspeed;
		}
	}


	if (keys['n'])
		level=3;
	if (keys['m'])
		level=2;



	for (auto &o : objects)
	{
		if(menuState == START && playScreen != nullptr && o != objects.front())
		{
			o->rotation.x = rotationX;
			o->rotation.y = rotationY;
			o->rotation.z = rotationZ;
		}
		o->update(deltaTime);
	}
	if(playScreen != nullptr)
		playScreen->update();


	glutPostRedisplay();
}



void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseX = x;
		mouseY = y;
	}
}

int main(int argc, char* argv[])
{
	
	soundInit();
	toggleBackgroundMusic();

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("IN GOOD SHAPE");
	//glutFullScreen();
	text->initText(width, height);

	if (cvInit() && menuState == START)
	{
		Main::BindCVMat2GLTexture(frame);
		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glEnable(GL_TEXTURE_2D);
	}

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouseClick);
	glutSpecialFunc(moveCube);

	glutPassiveMotionFunc(mouseMotion);

	glEnable(GL_DEPTH_TEST);

	init();

	//std::thread mainThread(glutMainLoop);
	std::thread openCVThread(objectDetectTest);
	//mainThread.join();
	openCVThread.detach();

	

	//objectDetectTest();
	glutMainLoop();
	dropSoundEngine();
	
	return 0;
}
