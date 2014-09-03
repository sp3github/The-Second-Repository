#pragma once
#include "Zombies.h"
#include <iostream>
#include <vector>


class SPZombie : public CZombies
{
public:
	SPZombie(void);
	~SPZombie(void);

	string zombiename;	

	int tile_size;

	void setPlayerName(string playername);

	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);
	void SpawnSP();
	int getLevel(int level);
	
	void CollisionEvent(CEntity &other, vector<CEntity*> & theArray);
};

