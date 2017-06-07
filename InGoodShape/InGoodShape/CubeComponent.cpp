#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <iostream>



CubeComponent::CubeComponent(float size)
{
	this->size = size;
}


CubeComponent::~CubeComponent()
{
}

void CubeComponent::draw()
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);

	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(0, 1, 0);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor3f(0, 0, 1);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, size, -size);
	glVertex3f(size, size, -size);
	glVertex3f(size, -size, -size);

	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, -size, size);

	glEnd();
}
