#pragma once
#include "Menu.h"


class PlayMenu : Menu
{
public:
	PlayMenu();
	~PlayMenu();
	virtual void update();
	virtual void draw();
	void drawCamera();
	void drawCameraWithOverlay();
	void drawCameraWhiteOverlay();
};

