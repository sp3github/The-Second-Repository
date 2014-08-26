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

	bool CheckCollision(CEntity *go, CEntity *other = NULL, bool m_bCheckUpwards = false, bool m_bCheckDownwards = false, bool m_bCheckLeft = false, bool m_bCheckRight = false);


	bool WallCollision(int left, int right, int top, int bottom);

	bool Collider(int x, int y);
};

