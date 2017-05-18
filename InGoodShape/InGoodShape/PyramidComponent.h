#pragma once

#include "DrawComponent.h"

class PyramidComponent : public DrawComponent
{
	float size;
	float height;
public:
	PyramidComponent(float size, float height);
	~PyramidComponent();

	virtual void draw() override;
};

