#pragma once
#include "Define.h"

#ifndef COBSTACLE_H
#define COBSTACLE_H

class CObstacle
{
private:
	bool spawnrate;
	int zombiecount;
	int maxzombiecount;
public:
	CObstacle(void);
	~CObstacle(void);
	CObstacle(int zc, int mzc, bool sr);

	int getZombiecount();

	void Spawn();
	void RenderObstalcle();
	void UpdateObstacle();
};
#endif

