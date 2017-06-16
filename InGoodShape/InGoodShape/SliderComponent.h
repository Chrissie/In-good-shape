#pragma once
#include "DrawComponent.h"
#include "GameObject.h"
#include "Menu.h"

class SliderComponent : public DrawComponent
{
	int length;
	Menu menu;
	int size;
	float pos;
public:
	SliderComponent(int length, int size, float pos);
	~SliderComponent();

	virtual void draw() override;

};

