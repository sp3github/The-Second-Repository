#pragma once
#include "Obstacle.h"

CObstacle::CObstacle(void)
{
	Set_X(rand()% 800);
	Set_Y(rand()% 600);  
}

CObstacle::~CObstacle(void)
{

}

int CObstacle::getZombieCount()
{
	return zombiecount;
}

void CObstacle::setZombieCount(int z)
{
	zombiecount = z;
}

void CObstacle::SetArray(vector<CEntity*> &theArrayofEntities)
{
	this->theArrayofEntities = &theArrayofEntities;
}

void CObstacle::SetFactory(CEntityFactory &theFactory)
{
	this->theFactory = &theFactory;
}
