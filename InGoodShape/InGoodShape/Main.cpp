// Standard includes.
#include <iostream>
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

// GL includes
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
#include "Main.h"

//sound
#include "Sound.h"


int mouseX = 0;
int mouseY = 0;

int width = 1920;
int height = 1080;

float rotationX = 0;
float rotationY = 0;
float deltaTime;
float mouseSpeedX = 0;
float mouseSpeedY = 0;

int xPos = 0;
int yPos = 0;

float oldX = 0;
float oldY = 0;

bool keys[256];

int lastTime = 0;


std::list<GameObject*> objects;

Text* text;
Menu menu;
MainMenu* mainMenu;
InstructionMenu* instructionMenu;
PlayMenu* playScreen;
OptionMenu* optionMenu;

bool selectedButtons[10];

enum MenuState { MAIN, INSTRUCTIONS, START, OPTIONS, EXIT} menuState;

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
			if (menuState == MAIN) menuState = EXIT;
		}
		if (keys[13]) //enter key
		{
			for (int i = 0; i < sizeof(selectedButtons); i++)
				selectedButtons[i] = false;
			switchMenu();
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
		rotationY -= deltaTime * 180;
	}
	if (x > oldX)
	{
		rotationY += deltaTime * 180;
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
	float deltaX = oldX - x;
	float deltaY = oldY - y;

	mouseSpeedX = (deltaX / deltaTime)/100;
	mouseSpeedY = (deltaY / deltaTime)/100;
	
	rotate(x, y);

	oldX = x;
	oldY = y;
	
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

	glPushMatrix();
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
	glPopMatrix();


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
	case EXIT:
		exit(0);
		break;
	}
}
	

void idle()
{
	if (cap.read(frame))
	{
		Main::BindCVMat2GLTexture(frame);
	}

	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

	if (keys['w'])
	{
		rotationX -= deltaTime * 180;
	}
	if (keys['s'])
	{
		rotationX += deltaTime * 180;
	}
	if (keys['a'])
	{
		rotationY -= deltaTime * 180;
	}
	if (keys['d'])
	{
		rotationY += deltaTime * 180;
	}



	for (auto &o : objects)
		o->update(deltaTime);

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
	glutFullScreen();
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

	glutMainLoop();
	dropSoundEngine();
	
	return 0;
}
