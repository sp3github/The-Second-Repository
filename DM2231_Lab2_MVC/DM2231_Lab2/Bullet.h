#pragma once
#include "Entity.h"

class bullet : public CEntity
{
public:
	bullet();
	~bullet();
	float HeroRotationRad;
	int power;

	void render(int mapOffset_x, int mapOffset_y);
	void update(float dt);

	bool SetPower(int power);
	bool SetAngle(float HeroRotation);
};

