#pragma once

#include "Items.h"

class CAmmo	:
	public CItems
{
public:
	CAmmo(void);
	~CAmmo(void);

	void update(float dt);
	void render(int mapOffset_x, int mapOffset_y);

};

