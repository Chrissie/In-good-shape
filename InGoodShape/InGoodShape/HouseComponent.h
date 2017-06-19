#pragma once
#include "DrawComponent.h"


class HouseComponent : public DrawComponent
{
	float height;
	float width;
	float length;
	int alfa;
public:
	HouseComponent(float height, float width, float length, int alfa);
	~HouseComponent();
	virtual void draw() override;
};

