#pragma once
#include "Map.h"
#include "Entity.h"

class Collision
{
	
public:

	Collision(CMap &theMap);
	Collision(void);
	~Collision(void);

	CMap * theMap;

	bool CheckCollision(CEntity go, CEntity other, bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft, bool m_bCheckRight);


	bool WallCollision(CEntity go);
};

