#include "SpecialZombie.h"


SpecialZombie::SpecialZombie(void)
{
	movementspeed = 100;
}


SpecialZombie::~SpecialZombie(void)
{
}

void SpecialZombie::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
{
	Vector3D<float> vel;
	Vector3D<float> pos;

	vel.Set(0.5,0.5,0.5);

	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX() - mapOffset_x, GetY() - mapOffset_y);

	Vector3D<float> theDiff((HeroPos * dt) - ZombiePos*dt);

	if(theDiff.Magnitude() > 0.5)
	{
		theDiff.Normalize();

		vel += theDiff;

		pos.Set(GetX(),GetY());
		pos += vel;

		Set_X(pos.x);
		Set_Y(pos.y);
	}
}
void SpecialZombie::render(int mapOffset_x, int mapOffset_y)
{

	glPushMatrix();
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
	glPushMatrix();
	//RENDER THE NAME OF THE GUY
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);		
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(0,0);
	glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
	glTexCoord2f(1,1); glVertex2f(0,tile_size);
	glTexCoord2f(0,1); glVertex2f(tile_size,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void SpecialZombie::SavePlayerStats(string name, int level)
{
	theLevel = level;
	theName = name;
}