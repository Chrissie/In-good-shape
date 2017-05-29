#pragma once

class GameObject;

class Component
{
	
public:
	Component();
	~Component();

	virtual void init() {};

	GameObject* gameObject;

	virtual void update(float elapsedTime) {};

	inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

