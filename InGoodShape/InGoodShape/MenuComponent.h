#pragma once
#include "Component.h"
#include <string>
#include "DrawComponent.h"


class MenuComponent : public DrawComponent
{
	std::string title;
	float fontSize;
public:
	MenuComponent(std::string Title, float fontSize = 1);
	~MenuComponent();

	virtual void update(float elapsedTime) override;
	virtual void draw();
};

