#include "SliderComponent.h"
#include <GL/freeglut.h>



SliderComponent::SliderComponent(int length, int size)
{
	this->length = length;
	this->size = size;
	//this->menu = menu;
}


SliderComponent::~SliderComponent()
{
}

void SliderComponent::draw()
{
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(gameObject->position.x, gameObject->position.y, 0);
	glVertex3f(gameObject->position.x, gameObject->position.y + 0.1, 0);
	glVertex3f(gameObject->position.x + length, gameObject->position.y + 0.1, 0);
	glVertex3f(gameObject->position.x + length, gameObject->position.y, 0);


	glVertex3f(gameObject->position.x +, gameObject->position.y-(size), 0);
	glVertex3f(gameObject->position.x, gameObject->position.y+(size), 0);
	glVertex3f(gameObject->position.x+1, gameObject->position.y+(size), 0);
	glVertex3f(gameObject->position.x+1, gameObject->position.y-(size), 0);

	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, -size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y +size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y +size, -size);

	//glVertex3f(gameObject->position.x -size, gameObject->position.y -size, -size);
	//glVertex3f(gameObject->position.x -size, gameObject->position.y -size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, -size);

	//glVertex3f(gameObject->position.x -size, gameObject->position.y-size, -size);
	//glVertex3f(gameObject->position.x -size, gameObject->position.y+ size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y+size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y-size, -size);

	//glVertex3f(gameObject->position.x -size, gameObject->position.y -size, -size);
	//glVertex3f(gameObject->position.x -size, gameObject->position.y+size, -size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y+ size, -size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, -size);

	//glVertex3f(gameObject->position.x -size, gameObject->position.y -size, size);
	//glVertex3f(gameObject->position.x -size, gameObject->position.y+size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y+ size, size);
	//glVertex3f(gameObject->position.x+size, gameObject->position.y -size, size);
	glEnd();
}