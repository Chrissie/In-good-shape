#pragma once
#include "Component.h"
#include <string>
#include "DrawComponent.h"


class MenuComponent : public DrawComponent
{
	
	float fontSize;
public:
	MenuComponent(std::string Title, float fontSize = 1);
	~MenuComponent();
	std::string title;

	virtual void update(float elapsedTime) override;
	virtual void draw();
};

