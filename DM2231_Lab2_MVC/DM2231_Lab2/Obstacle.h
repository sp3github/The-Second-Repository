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
	
	int getZombiecount();
	Vector3D<float> vel;
	Vector3D<float> pos;
	bool Spawn();
	void update();
	void render(int mapOffset_x, int mapOffset_y);
	
	int zombiecount;
	bool spawn;
	int maxzombiecount;
};
