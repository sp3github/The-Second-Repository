#include "EntityFactory.h"
#include <stdlib.h>

CEntityFactory::CEntityFactory(void)
{
}


CEntityFactory::~CEntityFactory(void)
{
}

CItems* CEntityFactory::Create(ItemsID id)
{
	CItems* theNewItems = NULL;

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
	default:
		{
		}
		break;
	}
	
	return theNewItems;
}