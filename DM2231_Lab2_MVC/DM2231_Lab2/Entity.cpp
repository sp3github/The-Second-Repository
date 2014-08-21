#include "Entity.h"


CEntity::CEntity(void)
{
	pos_x = 0;
	pos_y = 0;
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

void CEntity::update()
{

}
void CEntity::render()
{

}

bool CEntity::CollisionEvent()
{
	return false;
}