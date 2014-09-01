#pragma once
#include <cmath>
#include "Map.h"
#include "Ortho2D.h"
#include "Mouse.h"
#include "UI.h"
#include <stdio.h>
#include "EntityFactory.h"
#include <vector>
#include "PlayerInfo.h"
#include "Collision.h"
#include "State.h"
#include "gun.h"
#include "MVCtime.h"
#include "Zombies.h"
#include "Obstacle.h"

#define PI 3.1415f

class DM2231_Model
{
public:
	DM2231_Model(void);
	~DM2231_Model(void);
	// Update the model
	void Update(void);
	CMap TestMap;
	Ortho2D theOrtho2DSetUp;
	CMouse theMouseInfo;
	UI theUI;

	vector<CEntity*> ArrayofEntities;
	CEntityFactory theEntityFactory;

	CPlayerInfo * theHero;
	CEntity * theHeroEntity;
	CZombies * theZombie;

	gun thegun;

	Collision theCollision;

	CObstacle * theObstacle;

	float AnglefromHerotoMouse();

	State theState;
	void ConstrainHero();

	mvcTime * time;

	int IndexTime[10];

	bool SetTimeDefeat;

	void SetStart();

	/*int zombiecount;
	int getZombieCount();
	void update(int zombiecount);
};
