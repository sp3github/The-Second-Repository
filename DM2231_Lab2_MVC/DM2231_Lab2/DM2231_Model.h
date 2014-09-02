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
#include <string>
#include <iostream>

using namespace std;


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

	vector<std::shared_ptr<CEntity>> ArrayofEntities;
	CEntityFactory theEntityFactory;

	UI * ui;//printing 

	CPlayerInfo * theHero;
	CEntity * theHeroEntity;

	CZombies * theZombie;

	gun thegun;
	Casino * theCasino;
	Collision theCollision;

	CObstacle * theObstacle;

	float AnglefromHerotoMouse();

	State theState;
	void ConstrainHero();

	mvcTime * time;
	short int IndexTime;

	bool SetTimeDefeat;
	bool SetTimeCredit;
	bool SetTimeWin;
	bool SetTimePageToLearnShop;

	void SetStart(int level);

	short level;

	//zombie
	int zombie;
	int zombiecount;
	void setZombieCount(int z);
	int getZombieCount();
	void UpdateLimit();

	void DeleteVectorButHero();
};
