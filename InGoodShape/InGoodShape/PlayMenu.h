#pragma once
#include "Menu.h"
#include <opencv2/core/mat.hpp>


class PlayMenu : Menu
{
public:
	PlayMenu();
	~PlayMenu();
	virtual void update();
	virtual void draw();
	void drawCamera();
};

