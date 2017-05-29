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
#include "Text.h"
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
Text* text;

cv::VideoCapture cap(0);
cv::Mat frame;
GLuint *textures = new GLuint[1]{ 0 };

//returns true if init was succesful, else return false
bool cvInit()
{
	return cap.read(frame);
}

void BindCVMat2GLTexture(cv::Mat& image)
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
	instructionButton->position = ::Vec3f(0, 2, 0);
	objects.push_back(instructionButton);

	GameObject* startButton = new GameObject();
	startButton->addComponent(new CubeComponent(0.5));
	startButton->addComponent(new MenuComponent("START"));
	startButton->position = ::Vec3f(0, 0, 0);
	objects.push_back(startButton);

	GameObject* optionsButton = new GameObject();
	optionsButton->addComponent(new CubeComponent(0.5));
	optionsButton->addComponent(new MenuComponent("OPTIONS"));
	optionsButton->position = ::Vec3f(0, -2, 0);
	objects.push_back(optionsButton);

	//GameObject* exitButton = new GameObject();
	//exitButton->addComponent(new CubeComponent(0.5));
	//exitButton->addComponent(new MenuComponent("EXIT"));
	//exitButton->position = Vec3f(0, -4, 0);
	//objects.push_back(exitButton);

	//GameObject* exitButton = new GameObject();
	//exitButton->addComponent(new PyramidComponent(1, 2));
	//exitButton->addComponent(new SpinComponent(25));
	//exitButton->addComponent(new MenuComponent("EXIT"));
	//exitButton->position = Vec3f(0, -4, 0);
	//objects.push_back(exitButton);
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


	for (auto &o : objects)
		o->draw();	

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	//draw cube
	glPushMatrix();
	glTranslatef(xPos, yPos, 4);

	glTranslatef(0.5, 0.5, -0.5);
	glRotatef(rotationX, 1, 0, 0);
	glRotatef(rotationY, 0, 1, 0);
	glTranslatef(-0.5, -0.5, 0.5);

	drawCube();
	glPopMatrix();

	text->RenderText("IN GOOD SHAPE", (width/2)-(width/6), height/1.1, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	//text->RenderText("title", 100, 100, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	glutSwapBuffers();
}


int lastTime = 0;
void idle()
{
	if (cap.read(frame))
	{
		BindCVMat2GLTexture(frame);
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
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glutInit(&argc, argv);
	glutCreateWindow("IN GOOD SHAPE");
	text->initText(width, height);

	if (cvInit())
	{
		BindCVMat2GLTexture(frame);
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
	return 0;
}
