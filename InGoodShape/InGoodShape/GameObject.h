#pragma once

#include <list>
#include "Vec.h"

class Component;
class DrawComponent;

class GameObject
{

public:
	GameObject();
	~GameObject();


	Vec3f position;
	Vec3f rotation;
	Vec3f scale = Vec3f(1,1,1);

	std::list<DrawComponent*> drawComponents;

	std::list<Component*> components;

	template<class T>
	T* getComponent()
	{
		for(auto c : components)
		{
			if (dynamic_cast<T*>(c))
				return dynamic_cast<T*>(c);
		}
		return nullptr;
	}

	void addComponent(Component* component);
	void update(float elapsedTime);
	void draw();
};

