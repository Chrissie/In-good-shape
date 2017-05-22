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


int pos = 5;
extern int mouseX;
extern int mouseY;

extern Text* text;

extern int height;
extern int width;

int x;



MenuComponent::MenuComponent(std::string Title, float fontSize )
{
	title = Title;
	this->fontSize = fontSize;
	std::cout << title << std::endl;
}


MenuComponent::~MenuComponent()
{
}


void MenuComponent::update(float elapsedTime)
{

	if(mouseX != 0 || mouseY != 0)
	{
		//gameObject->position.x = pos;
		pos = -pos;
		mouseX = 0;
		mouseY = 0;
		//drawString();
	}
}

void MenuComponent::draw()
{
	text->RenderText(title, gameObject->position.x + (width/3), height - ((gameObject->position.y - 2)*-(height / 10.8)) - (height / 3), (fontSize * height) / 2160.0, glm::vec3(1.0f, 1.0f, 1.0f));
}
