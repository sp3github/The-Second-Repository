#pragma once
#include "Entity.h"
#include "Header.h"
#include "Vector3D.h"
class CObstacle : public CEntity
{
private:


public:
	CObstacle(void);
	~CObstacle(void);
	
	
	Vector3D<float> vel;
	Vector3D<float> pos;
	bool Spawn();
	
	void render(int mapOffset_x, int mapOffset_y);
	bool spawn;
	int maxzombiecount;

	int ammountZombie;
	int zombiecount;
	int getZombieCount();
	void setZombieCount(int z);
	void update();
};
