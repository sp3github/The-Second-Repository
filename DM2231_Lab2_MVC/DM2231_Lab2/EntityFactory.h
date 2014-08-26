#pragma once

#include "Entity.h"
#include "Items.h"
#include "Health.h"
#include "Ammo.h"
#include "Slowdown.h"
#include "PlayerInfo.h"


typedef int Entity;
#define HEALTH 0
#define AMMO 1
#define SLOWDOWN 2
#define PLAYER 3
#define BULLET 4


class CEntityFactory
{
public:
	CEntityFactory(void);
	~CEntityFactory(void);

	CEntity* Create(Entity id);
};

