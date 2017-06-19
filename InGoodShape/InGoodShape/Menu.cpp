#include "Menu.h"

Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::selectButton(int buttonID)
{
	for (int i = 0; i < sizeof(selectedButtons); i++)
		selectedButtons[i] = false;
	selectedButtons[buttonID] = true;
}

void Menu::deselectButtons()
{
	for (int i = 0; i < sizeof(selectedButtons); i++)
		selectedButtons[i] = false;
}


void Menu::draw()
{

}

void Menu::update()
{
	
}