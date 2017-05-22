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
	instructionButton->addComponent(new MenuComponent("Use hand gestures to control the game.", 0.8f));
	instructionButton->position = Vec3f(-400, 2, 0);
	objects.push_back(instructionButton);

	GameObject* startButton = new GameObject();
	startButton->addComponent(new MenuComponent("Fill selected surface on the screen using objects.", 0.8f));
	startButton->position = Vec3f(-400, 0, 0);
	objects.push_back(startButton);

	GameObject* saltyBitch = new GameObject();
	saltyBitch->addComponent(new MenuComponent("When every surface of the shape is filled, you go to the next level.", 0.8f));
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
