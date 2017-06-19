#include "HouseComponent.h"
#include <GL/freeglut.h>
#include "Main.h"


HouseComponent::HouseComponent(float height, float width, float lenght)
{
	this->height = height;
	this->width = width;
	this->length = lenght;

	for (auto b : isFilled)
		b = false;
	//isFilled[5] = true; //for testing purposes only
}


HouseComponent::~HouseComponent()
{
}

void HouseComponent::draw()
{
	if(isFilled[0])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glColor3f(0, 1, 0);

	//left and right
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-width, -height*0.6, -length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-width, -height*0.6, length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-width, height*0.6, length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-width, height*0.6, -length);
	glEnd();

	if (isFilled[1])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_QUADS);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, height*0.6, -length);
	glEnd();

	if (isFilled[2])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glColor3f(1, 0, 0);
	//top and bottom cube
	glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(width, -height*0.6, -length);
	glEnd();

	if (isFilled[3])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_QUADS);
	glVertex3f(-width, height*0.6, -length);
	glVertex3f(-width, height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, height*0.6, -length);
	glEnd();

	if (isFilled[4])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glColor3f(0, 0, 1);
	//front and back
	glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, height*0.6, -length);
	glVertex3f(width, height*0.6, -length);
	glVertex3f(width, -height*0.6, -length);
	glEnd();

	if (isFilled[5])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(-width, height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	glEnd();

	if (isFilled[6])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glColor3f(1.0, 0.078, 1.0);
	//roof
	glBegin(GL_QUADS);
	glVertex3f(0, -height*1.2, length);
	glVertex3f(0, -height*1.2, -length);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, -height*0.6, length);
	glEnd();

	if (isFilled[7])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_QUADS);
	glVertex3f(0, -height*1.2, length);
	glVertex3f(0, -height*1.2, -length);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, length);
	glEnd();

	if (isFilled[8])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_TRIANGLES);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(0, -height*1.2, length);
	glEnd();

	if (isFilled[9])
	{
		Main::drawFillTexture();
	} else {
		Main::drawWireframe();
	}
	glBegin(GL_TRIANGLES);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(0, -height*1.2, -length);
	glEnd();
}