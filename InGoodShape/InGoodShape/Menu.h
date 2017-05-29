#pragma once
#include <stddef.h>
#include <list>
#include "GameObject.h"


extern bool selectedButtons[10];
extern std::list<GameObject*> objects;
//extern float volume = 5;


class Menu
{
public:
	Menu();
	~Menu();
	void selectButton(int buttonID);
	void draw();
	void update();
};
