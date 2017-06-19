#pragma once

#include "DrawComponent.h"

class PyramidComponent : public DrawComponent
{
	float size;
	float height;
	int alfa;
public:
	PyramidComponent(float size, float height, int alfa);
	~PyramidComponent();

	virtual void draw() override;
};

