#include "EntityFactory.h"
#include <stdlib.h>

CEntityFactory::CEntityFactory(void)
{
}


CEntityFactory::~CEntityFactory(void)
{
}

CEntity* CEntityFactory::Create(Entity id)
{
	CEntity* theNewItems = NULL;

	switch(id)
	{
	case HEALTH:
		{
			theNewItems = new CHealth;
			theNewItems->ID = HEALTH;
		}
		break;
	case AMMO:
		{
			theNewItems = new CAmmo;
			theNewItems->ID = AMMO;
		}
		break;
	case SLOWDOWN:
		{
			theNewItems = new CSlowdown;
			theNewItems->ID = SLOWDOWN;
		}
		break;
	case PLAYER:
		{
			theNewItems = new CPlayerInfo;
			theNewItems->ID = PLAYER;
		}
		break;
	case BULLET:
		{
			theNewItems = new bullet;
			theNewItems->ID = BULLET;
		}
		break;
	case ZOMBIE:
		{
			theNewItems = new CZombies;
			theNewItems->ID = ZOMBIE;
		}
		break;
	default:
		{

		}
		break;
	}
	
	return theNewItems;
}