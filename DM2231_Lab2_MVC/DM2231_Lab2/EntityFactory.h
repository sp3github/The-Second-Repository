#pragma once
#include "EntitiesHeader.h"

class CEntityFactory
{
public:
	CEntityFactory(void);
	~CEntityFactory(void);

	CEntity* Create(Entity id);
};

