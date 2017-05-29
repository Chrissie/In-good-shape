#pragma once
#include "DrawComponent.h"
#include "GameObject.h"
#include "Menu.h"

class SliderComponent : public DrawComponent
{
	int length;
	Menu menu;
	int size;
public:
	SliderComponent(int length, int size);
	~SliderComponent();

	virtual void draw() override;

};

