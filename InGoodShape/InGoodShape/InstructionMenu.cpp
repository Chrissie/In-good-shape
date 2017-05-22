#include "InstructionMenu.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MenuComponent.h"


InstructionMenu::InstructionMenu()
{
	GameObject* backButton = new GameObject();
	backButton->addComponent(new CubeComponent(0.5));
	backButton->addComponent(new SpinComponent(25));
	backButton->addComponent(new MenuComponent("BACK"));
	backButton->position = Vec3f(-4, -4, 0);
	objects.push_back(backButton);

	GameObject* instructionButton = new GameObject();
	instructionButton->addComponent(new MenuComponent("Use your hands to control the game!"));
	instructionButton->position = Vec3f(-400, 2, 0);
	objects.push_back(instructionButton);

	GameObject* startButton = new GameObject();
	startButton->addComponent(new MenuComponent("Don't get mad if you lose!!"));
	startButton->position = Vec3f(-400, 0, 0);
	objects.push_back(startButton);

	GameObject* saltyBitch = new GameObject();
	saltyBitch->addComponent(new MenuComponent("Don't be a salty bitch!!!"));
	saltyBitch->position = Vec3f(-400, -2, 0);
	objects.push_back(saltyBitch);

	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("INSTRUCTIONS", 2));
	title->position = Vec3f(-400, 4, 0);
	objects.push_back(title);
}


InstructionMenu::~InstructionMenu()
{
	objects.clear();
}

void InstructionMenu::update()
{
}

void InstructionMenu::draw()
{
}
