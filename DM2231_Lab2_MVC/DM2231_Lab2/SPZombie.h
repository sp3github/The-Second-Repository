#pragma once
#include "Zombies.h"
#include <iostream>
#include <vector>
#include <string>


class SPZombie : public CZombies
{
public:
	SPZombie(void);
	~SPZombie(void);
	GLuint base;
	void GetBase(const GLuint &base);
	GLvoid printw(float x, float y, float z,const GLuint &base,const char *fmt, ...);

	string zombiename;
	string playername;

	int tile_size;
	short level;
	
	void setPlayerName(string playername);
	string getPlayerName();
	//void getLevel(short &level);

	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);
	void SpawnSP();
	void getLevel(short level);

	//void SetArrayFactory(vector<CEntity*> &theArray, CEntityFactory &theFac);
	
	void CollisionEvent(CEntity &other, vector<CEntity*> & theArray);
};

