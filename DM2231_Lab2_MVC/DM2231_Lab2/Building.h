#pragma once
#include "Entity.h"
#include <vector>

class Building : public CEntity
{
public:
	Building(void);
	~Building(void);

	void update(float dt);
	void render(int mapOffset_x, int mapOffset_y);
};

