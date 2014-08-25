#pragma once

#include "Items.h"

class CHealth	:
	public CItems
{
public:
	CHealth(void);
	~CHealth(void);

	void render();
};