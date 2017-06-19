#include "MainMenu.h"
#include "GameObject.h"
#include "CubeComponent.h"
#include "SpinComponent.h"
#include "MenuComponent.h"


MainMenu::MainMenu()
{
	GameObject* instructionButton = new GameObject();
	instructionButton->addComponent(new CubeComponent(0.5, 1));
	instructionButton->addComponent(new SpinComponent(25));
	instructionButton->addComponent(new MenuComponent("INSTRUCTIONS"));
	instructionButton->position = Vec3f(-4, 2, 0);
	objects.push_back(instructionButton);


	GameObject* startButton = new GameObject();
	startButton->addComponent(new CubeComponent(0.5, 1));
	startButton->addComponent(new SpinComponent(25));
	startButton->addComponent(new MenuComponent("START"));
	startButton->position = Vec3f(-4, 0, 0);
	objects.push_back(startButton);

	GameObject* optionsButton = new GameObject();
	optionsButton->addComponent(new CubeComponent(0.5, 1));
	optionsButton->addComponent(new SpinComponent(25));
	optionsButton->addComponent(new MenuComponent("OPTIONS"));
	optionsButton->position = Vec3f(-4, -2, 0);
	objects.push_back(optionsButton);

	GameObject* exitButton = new GameObject();
	exitButton->addComponent(new CubeComponent(0.5, 1));
	exitButton->addComponent(new SpinComponent(25));
	exitButton->addComponent(new MenuComponent("EXIT"));
	exitButton->position = Vec3f(-4, -4, 0);
	objects.push_back(exitButton);

	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("IN GOOD SHAPE", 2));
	title->position = Vec3f(-400, 4, 0);
	objects.push_back(title);
}


MainMenu::~MainMenu()
{
	objects.clear();
}

void MainMenu::update()
{
	
}

void MainMenu::draw()
{
	
}