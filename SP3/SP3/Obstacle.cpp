#include "Obstacle.h"

CObstacle::CObstacle(void)
{
}

CObstacle::~CObstacle(void)
{
}

CObstacle::CObstacle(int zc, int mzc, bool sr)
{
	spawnrate = sr;
	zombiecount = zc;
	maxzombiecount = mzc;
}

int CObstacle::getZombiecount()
{
	return zombiecount;
}

void Spawn()
{

}

void RenderObstacle()
{

}

void UpdateObstacle()
{

}