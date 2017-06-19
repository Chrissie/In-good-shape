#include "HouseComponent.h"
#include <GL/freeglut.h>
#include "Main.h"


HouseComponent::HouseComponent(float height, float width, float lenght, int alfa)
{
	this->height = height;
	this->width = width;
	this->length = lenght;
	this->alfa = alfa;

	for (auto b : isFilled)
		b = true;
	//isFilled[5] = true; //for testing purposes only
}


HouseComponent::~HouseComponent()
{
}

void HouseComponent::draw()
{
	glDisable(GL_TEXTURE_2D);
	//if(isFilled[0])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	glColor4f(0, 1, 0, alfa);

	//left and right
	glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(-width, height*0.6, length);
	glVertex3f(-width, height*0.6, -length);
	//glEnd();

	//if (isFilled[1])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	//glBegin(GL_QUADS);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, height*0.6, -length);
	//glEnd();

	//if (isFilled[2])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	glColor4f(1, 0, 0, alfa);
	//top and bottom cube
	//glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(width, -height*0.6, -length);
	//glEnd();

	//if (isFilled[3])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	//glBegin(GL_QUADS);
	glVertex3f(-width, height*0.6, -length);
	glVertex3f(-width, height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, height*0.6, -length);
	//glEnd();

	//if (isFilled[4])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	glColor4f(0, 0, 1, alfa);
	//front and back
	//glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, height*0.6, -length);
	glVertex3f(width, height*0.6, -length);
	glVertex3f(width, -height*0.6, -length);
	//glEnd();

	//if (isFilled[5])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	///glBegin(GL_QUADS);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(-width, height*0.6, length);
	glVertex3f(width, height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	//glEnd();

	//if (isFilled[6])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	glColor4f(1.0, 0.078, 1.0, alfa);
	//roof
	//glBegin(GL_QUADS);
	glVertex3f(0, -height*1.2, length);
	glVertex3f(0, -height*1.2, -length);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(-width, -height*0.6, length);
	//glEnd();

	//if (isFilled[7])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	//glBegin(GL_QUADS);
	glVertex3f(0, -height*1.2, length);
	glVertex3f(0, -height*1.2, -length);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, length);
	//glEnd();

	//if (isFilled[8])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	//glBegin(GL_TRIANGLES);
	glVertex3f(-width, -height*0.6, length);
	glVertex3f(width, -height*0.6, length);
	glVertex3f(0, -height*1.2, length);
	//glEnd();

	//if (isFilled[9])
	//{
	//	Main::drawFillTexture();
	//} else {
	//	Main::drawWireframe();
	//}
	//glBegin(GL_TRIANGLES);
	glVertex3f(-width, -height*0.6, -length);
	glVertex3f(width, -height*0.6, -length);
	glVertex3f(0, -height*1.2, -length);
	glEnd();
}