#pragma once

#include "Entity.h"
#include "Items.h"
#include "Health.h"
#include "Ammo.h"
#include "Slowdown.h"
#include "PlayerInfo.h"
#include "Zombies.h"
#include "Obstacle.h"


class CEntityFactory
{
public:
	CEntityFactory(void);
	~CEntityFactory(void);

	CEntity* Create(Entity id);
};

