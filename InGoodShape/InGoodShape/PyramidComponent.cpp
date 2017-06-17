#include "PyramidComponent.h"
#include <GL/freeglut.h>
#include "Main.h"


PyramidComponent::PyramidComponent(float size, float height)
{
	this->size = size;
	this->height = height;

	for (auto b : isFilled)
		b = false;
	isFilled[0] = true; //for testing purposes only
}

PyramidComponent::~PyramidComponent()
{
}

void PyramidComponent::draw()
{
	if (isFilled[0])
	{
		Main::drawFillTexture();
	}
	else {
		Main::drawWireframe();
	}
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, 0, size);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, 0, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, 0, -size);
	glEnd();

	if (isFilled[1])
	{
		Main::drawFillTexture();
	}
	else {
		Main::drawWireframe();
	}
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, 0, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, height, 0);
	glEnd();

	if (isFilled[2])
	{
		Main::drawFillTexture();
	}
	else {
		Main::drawWireframe();
	}
	glColor3f(0, 1, 0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, 0, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, height, 0);
	glEnd();

	if (isFilled[3])
	{
		Main::drawFillTexture();
	}
	else {
		Main::drawWireframe();
	}
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, 0, size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, height, 0);
	glEnd();

	if (isFilled[4])
	{
		Main::drawFillTexture();
	}
	else {
		Main::drawWireframe();
	}
	glColor3f(1, 0, 1);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, 0, -size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0, height, 0);
	glEnd();
	
}