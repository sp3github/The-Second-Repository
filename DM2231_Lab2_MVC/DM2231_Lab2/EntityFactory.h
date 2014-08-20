#pragma once

#include "Entity.h"
#include "Items.h"
#include "Health.h"
#include "Ammo.h"
#include "Slowdown.h"

typedef int ItemsID;
#define HEALTH 0
#define AMMO 1
#define SLOWDOWN 2

class CEntityFactory
{
public:
	CEntityFactory(void);
	~CEntityFactory(void);

	CItems* Create(ItemsID);
};

