#pragma once
#include "Zombies.h"
#include "DM2231_Model.h"
#include "State.h"
#include <iostream>
#include <vector>

DM2231_Model * theModel;
State theState;

class SPZombie : public CZombies
{
public:
	SPZombie(void);
	~SPZombie(void);

	string zombiename;	

	int tile_size;

	string setPlayerName(string playername);

	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);
	void SpawnSP();
	int getLevel(int level);
	void getDeathState(State theState);
	
	vector<CEntity*>::iterator  CollisionEvent(CEntity &other, vector<CEntity*> & theArray);
};

