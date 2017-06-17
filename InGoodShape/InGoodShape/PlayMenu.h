#pragma once
#include "Menu.h"

class Main;

class PlayMenu : Menu
{
public:
	PlayMenu();
	~PlayMenu();
	virtual void update();
	virtual void draw();
	void drawCamera();
	void switchLevel();
};

