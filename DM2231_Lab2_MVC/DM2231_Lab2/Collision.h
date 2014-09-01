#pragma once
#include "Map.h"
#include "Entity.h"
#include <vector>

class Collision
{
	
public:


	Collision(void);
	Collision(CMap &theMap, vector<CEntity*> & theArray);
	~Collision(void);

	CMap * theMap;
	vector<CEntity*> * theArray;

	bool CheckCollision(CEntity *go, CEntity *other = NULL, bool m_bCheckUpwards = false, bool m_bCheckDownwards = false, bool m_bCheckLeft = false, bool m_bCheckRight = false, bool CheckPos = false);


	bool WallCollision(int left, int right, int top, int bottom);

	bool Collider(int x, int y);
};

