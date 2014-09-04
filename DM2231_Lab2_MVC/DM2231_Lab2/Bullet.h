#pragma once
#include "Entity.h"
#include "vector3D.h"
#include "PlayerInfo.h"


using namespace std;

class bullet : public CEntity
{
public:
	CPlayerInfo * theHero;

	float HeroRotationRad;
	int power;

	void render(int mapOffset_x, int mapOffset_y);
	void update(float dt);

	bool SetPower(int power, int movementspeed);
	bool SetAngle(float HeroRotation);

	void CollisionEvent(CEntity &other, vector<CEntity*> & theArray);
	void SetHero(CPlayerInfo & theHero);

	bullet();
	~bullet();
};

