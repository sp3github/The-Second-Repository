#pragma once
#include "EntityFactory.h"

CEntityFactory::CEntityFactory(void)
{
}


CEntityFactory::~CEntityFactory(void)
{
}

CEntity* CEntityFactory::Create(Entity id)
{
	//CEntity* theNewItems = NULL;
	//std::shared_ptr<CEntity> theNewItems;
	switch(id)
	{
	case HEALTH:
		{
			std::shared_ptr<CEntity> theNewItems (new CHealth);
			theNewItems->ID = HEALTH;
		}
		break;
	case AMMO:
		{
			std::shared_ptr<CEntity> theNewItems(new CAmmo);
			theNewItems->ID = AMMO;
		}
		break;
	case SLOWDOWN:
		{
			std::shared_ptr<CEntity> theNewItems(new CSlowdown);
			theNewItems->ID = SLOWDOWN;
		}
		break;
	case PLAYER:
		{
			std::shared_ptr<CEntity> theNewItems(new CPlayerInfo);
			theNewItems->ID = PLAYER;
		}
		break;
	case BULLET:
		{
			std::shared_ptr<CEntity> theNewItems(new bullet);
			theNewItems->ID = BULLET;
		}
		break;
	case ZOMBIE:
		{
			std::shared_ptr<CEntity> theNewItems(new CZombies);
			theNewItems->ID = ZOMBIE;
		}
		break;
	case BUILDING:
		{
			std::shared_ptr<CEntity> theNewItems(new Building);
			theNewItems->ID = BUILDING;
		}
		break;
	default:
		{

		}
		break;
	}
}