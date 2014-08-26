#include "Entity.h"
#include "Health.h"
#include "PlayerInfo.h"

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

void CEntity::update()
{

}
void CEntity::render()
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(300,300, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glScalef(3,3,3);
	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(0, 0);
	glTexCoord2f(0, 0); glVertex2f(0, tile_size);
	glTexCoord2f(1, 0); glVertex2f(tile_size, tile_size);
	glTexCoord2f(1, 1); glVertex2f(tile_size, 0);
	glEnd();
	glPopMatrix();
}

bool CEntity::CollisionEvent(CEntity &other)
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

