#pragma once
#include "DrawComponent.h"


class HouseComponent : public DrawComponent
{
	float height;
	float width;
	float length;
public:
	HouseComponent(float height, float width, float length);
	~HouseComponent();
	virtual void draw() override;
};

