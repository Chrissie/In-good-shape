#include "SliderComponent.h"
#include <GL/freeglut.h>
#include "Main.h"



SliderComponent::SliderComponent(int length, int size, float pos)
{
	this->length = length;
	this->size = size;
	this->pos = pos;
}


SliderComponent::~SliderComponent()
{
}

void SliderComponent::draw()
{
	this->pos = volume/10;

	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(gameObject->position.x, gameObject->position.y, 0);
	glVertex3f(gameObject->position.x, gameObject->position.y + 0.1, 0);
	glVertex3f(gameObject->position.x + length, gameObject->position.y + 0.1, 0);
	glVertex3f(gameObject->position.x + length, gameObject->position.y, 0);


	glVertex3f(gameObject->position.x+pos, gameObject->position.y-(size), 0);
	glVertex3f(gameObject->position.x+pos, gameObject->position.y+(size), 0);
	glVertex3f(gameObject->position.x+pos+1, gameObject->position.y+(size), 0);
	glVertex3f(gameObject->position.x+pos+1, gameObject->position.y-(size), 0);

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