#include "PlayMenu.h"
#include "MenuComponent.h"


PlayMenu::PlayMenu()
{
	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("Play the game!"));
	title->position = Vec3f(-400, 4, 0);
	objects.push_back(title);
}


PlayMenu::~PlayMenu()
{
}

void PlayMenu::update()
{
	
}

void PlayMenu::draw()
{
}