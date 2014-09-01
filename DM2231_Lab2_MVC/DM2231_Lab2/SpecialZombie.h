#pragma once
#include "zombies.h"
#include <string>

using namespace std;

class SpecialZombie :
	public CZombies
{
public:
	SpecialZombie(void);
	~SpecialZombie(void);

	void SavePlayerStats(string name, int level);
	string theName;

	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);
	int theLevel;
};

