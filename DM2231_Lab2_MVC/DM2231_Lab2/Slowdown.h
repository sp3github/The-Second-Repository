#pragma once

#include "Items.h"

class CSlowdown	:
	public CItems
{
public:
	CSlowdown(void);
	~CSlowdown(void);

	void update();
	void render(int mapOffset_x, int mapOffset_y);
};

