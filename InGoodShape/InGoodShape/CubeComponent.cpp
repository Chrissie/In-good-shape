#include "CubeComponent.h"
#include <GL/freeglut.h>
#include <iostream>



CubeComponent::CubeComponent(float size, int alfa)
{
	this->size = size;
	this->alfa = alfa;
}


CubeComponent::~CubeComponent()
{
}

void CubeComponent::draw()
{
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor4f(1, 0, 0, alfa);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(-size, size, size);
	glVertex3f(-size, size, -size);

	glVertex3f(size, -size, -size);
	glVertex3f(size, -size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor4f(0, 1, 0, alfa);
	glVertex3f(-size, -size, -size);
	glVertex3f(-size, -size, size);
	glVertex3f(size, -size, size);
	glVertex3f(size, -size, -size);

	glVertex3f(-size, size, -size);
	glVertex3f(-size, size, size);
	glVertex3f(size, size, size);
	glVertex3f(size, size, -size);

	glColor4f(0, 0, 1, alfa);
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
