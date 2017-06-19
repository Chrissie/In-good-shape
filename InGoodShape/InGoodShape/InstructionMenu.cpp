#include "InstructionMenu.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MenuComponent.h"


InstructionMenu::InstructionMenu()
{
	GameObject* backButton = new GameObject();
	backButton->addComponent(new CubeComponent(0.5, 1));
	backButton->addComponent(new SpinComponent(25));
	backButton->addComponent(new MenuComponent("BACK"));
	backButton->position = Vec3f(-4, -4, 0);
	objects.push_back(backButton);

	GameObject* instructionButton = new GameObject();
	instructionButton->addComponent(new MenuComponent("Use the arrows and circle to control the game.", 0.7f));
	instructionButton->position = Vec3f(-450, 2, 0);
	objects.push_back(instructionButton);

	GameObject* startButton = new GameObject();
	startButton->addComponent(new MenuComponent("Fill selected surface on the screen using objects.", 0.7f));
	startButton->position = Vec3f(-450, 0, 0);
	objects.push_back(startButton);

	GameObject* instructionText = new GameObject();
	instructionText->addComponent(new MenuComponent("If green checkmark, show the circle.", 0.7f));
	instructionText->position = Vec3f(-450, -2, 0);
	objects.push_back(instructionText);

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
