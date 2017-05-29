// Standard includes.
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GL/freeglut.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
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


void reshape(int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int  y)
{
	switch (key) {
	case 27: exit(0);
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
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);

	//back
	glColor3f(1, 0.5, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 0, -1);

	//left side
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, -1);
	glVertex3f(0, 0, -1);

	//right side
	glColor3f(0, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 0, -1);

	//bottom
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, -1);
	glVertex3f(0, 0, -1);

	//top
	glColor3f(1, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, -1);
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
	if (keys['u'])
	{
		
	}

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
	//glTranslatef(xPos, yPos, 0);

	//glTranslatef(0.5, 0.5, -0.5);
	//glRotatef(rotationX, 1, 0, 0);
	//glRotatef(rotationY, 0, 1, 0);
	//glTranslatef(-0.5, -0.5, 0.5);

	//drawCube();
	//glPopMatrix();

	//text->RenderText("IN GOOD SHAPE", (width/8), height/1.2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

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
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - lastTime) / 1000.0f;
	lastTime = currentTime;

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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("IN GOOD SHAPE");
	glutFullScreen();
	text->initText(width, height);

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

	return 0;
}
