#include "Entity.h"


CEntity::CEntity(void)
{
	pos_x = 10;
	pos_y = 10;
	movementspeed = 0;
	tile_size = 24;
}


CEntity::~CEntity(void)
{
}

int CEntity::GetX(void)
{
	return pos_x;
}

int CEntity::GetY(void)
{
	return pos_y;
}

void CEntity::SetPos(const int pos_x, const int pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void CEntity::update(float dt)
{
	
}

void CEntity::update(int zombiecount)
{
	
}

void CEntity::update(int herox, int heroy, float dt)
{

}

void CEntity::render(int mapOffset_x, int mapOffset_y)
{
	
}

void CEntity::renderN(int mapOffset_x, int mapOffset_y)
{
	
}
void CEntity::renderF(int mapOffset_x, int mapOffset_y)
{
	
}
void CEntity::renderS(int mapOffset_x, int mapOffset_y)
{
	
}

bool CEntity::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	return false;
}

void CEntity::Set_Y(int pos_y)
{
	this->pos_y = pos_y;
}

void CEntity::Set_X(int pos_x)
{
	this->pos_x = pos_x;
}
