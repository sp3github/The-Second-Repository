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
#include "QuadTree.h"

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

	vector<CEntity*> ArrayofEntities;
	CEntityFactory theEntityFactory;

	//UI * ui;//printing 

	CPlayerInfo * theHero;
	CZombies * theZombie;
	CEntity * theHeroEntity;



	gun thegun;
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
	bool SetTimeStoryIn;

	void SetStart(int level);

	short level;

	//zombie
	int zombie;
	int zombiecount;
	void setZombieCount(int z);
	int getZombieCount();
	void UpdateLimit();

	void DeleteVectorButHero();
	void Collision();

	QuadTree * quad;

	float theMonWidth;
	float theMonHeight;

	float Wratio;
	float Hratio;
};
