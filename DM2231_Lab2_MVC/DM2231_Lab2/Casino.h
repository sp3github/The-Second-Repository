#pragma once
#include "Entity.h"
#include "EntityFactory.h"
#include <vector>

class Casino : public CEntity
{
public:
	Casino(void);
	~Casino(void);

	int maxzombiecount;

	void Spawn();

	void render(int mapOffset_x, int mapOffset_y);
	void update(float dt);
};

