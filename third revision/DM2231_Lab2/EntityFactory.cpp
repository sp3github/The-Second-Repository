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
		}
		break;
	case AMMO:
		{
			theNewItems = new CAmmo;
		}
		break;
	case SLOWDOWN:
		{
			theNewItems = new CSlowdown;
		}
		break;
	case PLAYER:
		{
			theNewItems = new CPlayerInfo;
		}
		break;
	case ZOMBIE:
		{
			theNewItems = new CZombies;
			break;
		}
	case OBSTACLE:
		{
			theNewItems = new CObstacle;
			break;
		}
	default:
		{

		}
		break;
	}
	
	return theNewItems;
}