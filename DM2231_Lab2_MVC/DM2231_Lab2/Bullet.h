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
	void update(float dt);

	bool SetPower(int power);
	bool SetAngle(float HeroRotation);

	vector<CEntity*>::iterator CollisionEvent(CEntity &other, vector<CEntity*> & theArray);

	bullet();
	~bullet();
};

