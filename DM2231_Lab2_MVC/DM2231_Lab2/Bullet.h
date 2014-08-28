#pragma once
#include "Entity.h"
#include "vector3D.h"


using namespace std;

class bullet : public CEntity
{
public:
	float HeroRotationRad;
	int power;

	void render(int mapOffset_x, int mapOffset_y);
	void update();

	bool SetPower(int power);
	bool SetAngle(float HeroRotation);


	bullet();
	~bullet();
};

