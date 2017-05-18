// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include "MenuComponent.h"
#include "GameObject.h"
#include <stdio.h>
#include <iostream>
#include <GL/freeglut.h>
#include  <string.h>
#include <detail/type_vec3.hpp>



#include "Text.h"


std::string title;
int pos = 5;
extern int mouseX;
extern int mouseY;
//unsigned char text[30];
extern Text* text;

int x;


MenuComponent::MenuComponent(std::string Title)
{
	title = Title;


}


MenuComponent::~MenuComponent()
{
}

//void drawString()
//{
//	std::cout << title << std::endl;
//
//	const char * c = title.c_str();
//	strcpy((char*)text, c);
//
//
//	glPushMatrix();
//	glTranslatef(0, 5, 0);
//	glColor3f(0, 0, 0);
//	glutStrokeString(GLUT_STROKE_ROMAN, text);
//	glPopMatrix();
//}

void MenuComponent::update(float elapsedTime)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	text->RenderText(title, 500, 500, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	glPopMatrix();
	if(mouseX != 0 || mouseY != 0)
	{
		//gameObject->position.x = pos;
		pos = -pos;
		mouseX = 0;
		mouseY = 0;
		//drawString();
	}
	//glutSwapBuffers();
}
