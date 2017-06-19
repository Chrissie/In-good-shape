#include "PyramidComponent.h"
#include <GL/freeglut.h>
#include "Main.h"


PyramidComponent::PyramidComponent(float size, float height, int alfa)
{
	this->size = size;
	this->height = height;
	this->alfa = alfa;

	for (auto b : isFilled)
		b = true;
}

PyramidComponent::~PyramidComponent()
{
}

void PyramidComponent::draw()
{
	glDisable(GL_TEXTURE_2D);
	//if (isFilled[0])
	//{
	//	Main::drawFillTexture();
	//}
	//else {
	//	Main::drawWireframe();
	//}
	glColor4f(1, 0, 0, alfa);
	glBegin(GL_TRIANGLES);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, size);

	glVertex3f(-size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, -size);
	//glEnd();

	//if (isFilled[1])
	//{
	//	Main::drawFillTexture();
	//}
	//else {
	//	Main::drawWireframe();
	//}
	glColor4f(0, 0, 1, alfa);
	//glBegin(GL_TRIANGLES);
	glVertex3f(-size, 0, size);
	glVertex3f(-size, 0, -size);
	glVertex3f(0, height, 0);
	//glEnd();

	//if (isFilled[2])
	//{
	//	Main::drawFillTexture();
	//}
	//else {
	//	Main::drawWireframe();
	//}
	glColor4f(0, 1, 0, alfa);
	//glBegin(GL_TRIANGLES);
	glVertex3f(-size, 0, size);
	glVertex3f(size, 0, size);
	glVertex3f(0, height, 0);
	//glEnd();

	//if (isFilled[3])
	//{
	//	Main::drawFillTexture();
	//}
	//else {
	//	Main::drawWireframe();
	//}
	glColor4f(1, 1, 0, alfa);
	//glBegin(GL_TRIANGLES);
	glVertex3f(size, 0, size);
	glVertex3f(size, 0, -size);
	glVertex3f(0, height, 0);
	//glEnd();

	//if (isFilled[4])
	//{
	//	Main::drawFillTexture();
	//}
	//else {
	//	Main::drawWireframe();
	//}
	glColor4f(1, 0, 1, alfa);
	//glBegin(GL_TRIANGLES);
	glVertex3f(size, 0, -size);
	glVertex3f(-size, 0, -size);
	glVertex3f(0, height, 0);
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(size, 0, -size);
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, 0, -size);
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(0, height, 0);
	glEnd();
	
}