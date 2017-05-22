#include "PyramidComponent.h"
#include <GL/freeglut.h>




PyramidComponent::PyramidComponent(float size, float height)
{
	this->size = size;
	this->height = height;
}


PyramidComponent::~PyramidComponent()
{
}

void PyramidComponent::draw()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, size);

	glVertex3f(-size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, -size);

	glVertex3f(-size, 0, size);
	glVertex3f(-size, 0, -size);
	glVertex3f(0, height, 0);

	glColor3f(0, 1, 0);
	glVertex3f(-size, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(0, height, 0);

	glColor3f(1, 0, 0);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(0, height, 0);

	glColor3f(0, 0, 1);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, -size);
	glVertex3f(0, height, 0);

	glColor3f(0, 0, 1);


	glEnd();
}
