#include <GL/freeglut.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "GameObject.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MenuComponent.h"
#include "PyramidComponent.h"
#include <chrono>

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

std::list<GameObject*> objects;

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

	keys[key] = true;
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

	GameObject* instructionButton = new GameObject();
	instructionButton->addComponent(new CubeComponent(0.5));
	instructionButton->addComponent(new MenuComponent("INSTRUCTIONS"));
	instructionButton->position = Vec3f(0, 2, 0);
	objects.push_back(instructionButton);

	GameObject* startButton = new GameObject();
	startButton->addComponent(new CubeComponent(0.5));
	startButton->addComponent(new MenuComponent("START"));
	startButton->position = Vec3f(0, 0, 0);
	objects.push_back(startButton);

	GameObject* optionsButton = new GameObject();
	optionsButton->addComponent(new CubeComponent(0.5));
	optionsButton->addComponent(new MenuComponent("OPTIONS"));
	optionsButton->position = Vec3f(0, -2, 0);
	objects.push_back(optionsButton);

	//GameObject* exitButton = new GameObject();
	//exitButton->addComponent(new CubeComponent(0.5));
	//exitButton->addComponent(new MenuComponent("EXIT"));
	//exitButton->position = Vec3f(0, -4, 0);
	//objects.push_back(exitButton);

	GameObject* exitButton = new GameObject();
	exitButton->addComponent(new PyramidComponent(1, 2));
	exitButton->addComponent(new SpinComponent(25));
	exitButton->addComponent(new MenuComponent("EXIT"));
	exitButton->position = Vec3f(0, -4, 0);
	objects.push_back(exitButton);
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

	for (auto &o : objects)
		o->draw();

	//draw cube
	glPushMatrix();
	glTranslatef(xPos, yPos, 0);

	glTranslatef(0.5, 0.5, -0.5);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	glTranslatef(-0.5, -0.5, 0.5);

	drawCube();
	glPopMatrix();


	glutSwapBuffers();
}


int lastTime = 0;
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