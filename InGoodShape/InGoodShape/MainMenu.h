#pragma once
#include "Menu.h"

class MainMenu : Menu
{
public:
	MainMenu();
	virtual ~MainMenu();
	virtual void update();
	virtual void draw();
};

