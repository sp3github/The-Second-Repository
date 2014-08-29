#include "Entity.h"


CEntity::CEntity(void)
{
	pos_x = 10;
	pos_y = 10;
	movementspeed = 0;
	tile_size = 24;
	hp = 100;
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

void CEntity::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
{

}

void CEntity::render(int mapOffset_x, int mapOffset_y)
{
	
}

 vector<CEntity*>::iterator CEntity::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	return theArray.end();
}

void CEntity::Set_Y(int pos_y)
{
	this->pos_y = pos_y;
}

void CEntity::Set_X(int pos_x)
{
	this->pos_x = pos_x;
}
