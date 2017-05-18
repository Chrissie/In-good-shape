#pragma once
#include "Component.h"
#include <string>

class MenuComponent : public Component
{
public:
	MenuComponent(std::string Title);
	~MenuComponent();

	virtual void update(float elapsedTime) override;
};

