#pragma once
#include "Menu.h"
class OptionMenu : public Menu
{
public:
	OptionMenu();
	~OptionMenu();
	virtual void draw();
	virtual void update();
};

