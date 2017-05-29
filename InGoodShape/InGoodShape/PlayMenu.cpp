#include "PlayMenu.h"
#include "MenuComponent.h"

GLuint camera;

PlayMenu::PlayMenu()
{
	GameObject* title = new GameObject();
	title->addComponent(new MenuComponent("Play the game!"));
	title->position = ::Vec3f(-400, 4, 0);
	objects.push_back(title);
}


PlayMenu::~PlayMenu()
{
}

void PlayMenu::updateTexture(GLuint tex)
{
	camera = tex;
	glBindTexture(GL_TEXTURE_2D, camera);
	glEnable(GL_TEXTURE_2D);
}

void PlayMenu::update()
{
	
}

void PlayMenu::draw()
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2d(0, 0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2d(0, 200);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2d(200, 200);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2d(200, 0);
	glEnd();
}