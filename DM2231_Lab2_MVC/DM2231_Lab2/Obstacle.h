#pragma once

#include "EntitiesHeader.h"
#include "EntityFactory.h"
#include <vector>


class CObstacle : public CEntity 
{

public:
	CObstacle(void);
	~CObstacle(void);

	std::vector<CEntity*> * theArrayofEntities;
	CEntityFactory * theFactory;

	Vector3D<float> vel;
	Vector3D<float> pos;

	int tile_size;

	int zombiecount;
	int getZombieCount();
	void setZombieCount(int z);

	void SetArray(vector<CEntity *> & theArrayofEntities);
	void SetFactory(CEntityFactory & theFactory);
};
