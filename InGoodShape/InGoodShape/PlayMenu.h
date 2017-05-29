#pragma once
#include "Menu.h"
// freeglut
#include <GL/freeglut.h>

class PlayMenu : Menu
{
public:
	PlayMenu();
	~PlayMenu();
	virtual void updateTexture(GLuint tex);
	virtual void update();
	virtual void draw();
};

