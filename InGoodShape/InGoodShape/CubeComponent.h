#pragma once

#include "DrawComponent.h"

class CubeComponent : public DrawComponent
{
	float size;
	int alfa;
public:
	CubeComponent(float size, int alfa);
	~CubeComponent();

	virtual void draw() override;
};

