#pragma once
#include "Entity.h"
#include "vector3D.h"


using namespace std;

class bullet : public CEntity
{
public:
	float HeroRotationRad;

	void render(int mapOffset_x, int mapOffset_y);
	void update();

	bool GetAngle(float HeroRotation);


	bullet();
	~bullet();
};

