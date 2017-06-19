#include "OptionMenu.h"
#include "MenuComponent.h"
#include "SpinComponent.h"
#include "CubeComponent.h"
#include "SliderComponent.h"


OptionMenu::OptionMenu()
{
	GameObject* backButton = new GameObject();
	backButton->addComponent(new CubeComponent(0.5, 1));
	backButton->addComponent(new SpinComponent(25));
	backButton->addComponent(new MenuComponent("BACK"));
	backButton->position = Vec3f(-4, -4, 0);
	objects.push_back(backButton);

	GameObject* volume = new GameObject();
	volume->addComponent(new MenuComponent("Volume", 0.8f));
	volume->position = Vec3f(-450, 2, 0);
	objects.push_back(volume);

	GameObject* slider = new GameObject();
	slider->addComponent(new SliderComponent(10, 1, 5));
	slider->position = Vec3f(-4, 0, 0);
	objects.push_back(slider);


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
