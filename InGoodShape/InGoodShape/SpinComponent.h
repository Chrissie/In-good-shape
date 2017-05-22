#pragma once

#include "Component.h"


class SpinComponent : public Component
{


public:
	SpinComponent(float speed, bool xRot = false, bool yRot = false, bool zRot = false);
	~SpinComponent();

	void init() override;


	bool xRot;
	bool yRot;
	bool zRot;
	float speed;

	virtual void update(float elapsedTime) override;

	virtual void spinAll();
	virtual void spinX();
	virtual void stopSpin();
};

