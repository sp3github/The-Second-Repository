#include "Zombies.h"

CZombies::CZombies(void)
: CurrentState(0)
, IDLE(0)
, ATTACK(0)
, REPEL(0)
, hero_x(0)
, hero_y(0)
, i(0)
{
	Set_X(rand()% 800);
	Set_Y(rand()% 600);  
	
}

CZombies::~CZombies(void)
{
}

bool CZombies::ChangeState(const int newState)
{
	return false;
}

void CZombies::deceasingHealth(int num)
{
	health = num;
} 

int CZombies::getHealth()
{
	return health;
}

int CZombies::getMoneySteal()
{
	return moneysteal;
}

bool CZombies::isDead()
{
	return isdead;
}

int CZombies::CalculateDistance(int hero_x, int hero_y)
{
	return ( (hero_x - GetX()) * (hero_x - GetX()) + (hero_x - GetY()) * (hero_x - GetY()));
}

void CZombies::update()
{	

}

void CZombies::setStats(int health, int moneysteal)
{
	health = 10;
	moneysteal = 20;

}
void CZombies::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
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

void CZombies::render(int mapOffset_x, int mapOffset_y)
{	
	//Zombies
	glPushMatrix();
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
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
