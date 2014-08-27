#pragma once

#include "Items.h"

class CHealth	:
	public CItems
{
public:
	CHealth(void);
	~CHealth(void);

	void update();
	void render(int mapOffset_x, int mapOffset_y);
};