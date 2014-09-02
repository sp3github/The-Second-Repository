#pragma once
#include "Casino.h"
#include "EntitiesHeader.h"
#include "EntityFactory.h"
#include <vector>

class CObstacle : public CEntity 
{

public:
	CObstacle(void);
	~CObstacle(void);

	vector<std::shared_ptr<CEntity>> * theArrayofEntities;
	CEntityFactory * theFactory;

	Vector3D<float> vel;
	Vector3D<float> pos;

	int tile_size;

	int zombiecount;
	int getZombieCount();
	void setZombieCount(int z);

	void SetArray(vector<std::shared_ptr<CEntity>> & theArrayofEntities);
	void SetFactory(CEntityFactory & theFactory);
};
