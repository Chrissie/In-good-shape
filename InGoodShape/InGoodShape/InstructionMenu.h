#pragma once
#include "Menu.h"

class InstructionMenu : Menu
{
public:
	InstructionMenu();
	~InstructionMenu();
	virtual void update();
	virtual void draw();
};

