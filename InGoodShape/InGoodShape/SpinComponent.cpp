#include "SpinComponent.h"
#include "GameObject.h"



SpinComponent::SpinComponent(float speed, bool xRot, bool yRot, bool zRot)
{
	this->speed = speed;
	this->xRot = xRot;
	this->yRot = yRot;
	this->zRot = zRot;
}

void SpinComponent::init()
{

}


SpinComponent::~SpinComponent()
{
}

void SpinComponent::update(float elapsedTime)
{
	if(xRot)
		gameObject->rotation.x += elapsedTime * speed;
	if (yRot)
		gameObject->rotation.y += elapsedTime * speed;
	if (zRot)
		gameObject->rotation.z += elapsedTime * speed;

}

void SpinComponent::spinAll()
{
	xRot = true;
	yRot = true;
	zRot = true;
}

void SpinComponent::spinX()
{
	xRot = true;
	yRot = false;
	zRot = false;
}

void SpinComponent::stopSpin()
{
	xRot = false;
	yRot = false;
	zRot = false;
}

