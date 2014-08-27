#pragma once
#include "Entity.h"
#include "Header.h"

class CObstacle : public CEntity
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
	void UpdateObstacle();
	void renderObstacle();
};
