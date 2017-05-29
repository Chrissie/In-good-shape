#include "OptionMenu.h"
#include "MenuComponent.h"
#include "SpinComponent.h"
#include "CubeComponent.h"


OptionMenu::OptionMenu()
{
	GameObject* backButton = new GameObject();
	backButton->addComponent(new CubeComponent(0.5));
	backButton->addComponent(new SpinComponent(25));
	backButton->addComponent(new MenuComponent("BACK"));
	backButton->position = Vec3f(-4, -4, 0);
	objects.push_back(backButton);

	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("OPTIONS"));
	title->position = Vec3f(-400, 4, 0);
	objects.push_back(title);
}


OptionMenu::~OptionMenu()
{
	objects.clear();
}

void OptionMenu::draw()
{
	
}

void OptionMenu::update()
{
	
}
