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
	Set_Y(rand()% 40+405);  

	vel.Set(1,1,1);
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

int CZombies::CalculateDistance(const int hero_x, const int hero_y)
{
	return ( (hero_x - GetX()) * (hero_x - GetX()) + (hero_x - GetY()) * (hero_x - GetY()));
}

void CZombies::update()
{	
	//int pos_x;
	//int pos_y;

	//Set_X(pos_x);
	//Set_Y(pos_y);
	//cout << "UPDATE: CLEAR!!!" << endl;

	//if (CalculateDistance(hero_x, hero_y) < 100000.0f)
	//{
	//	if (CalculateDistance(hero_x, hero_y) < 625.0f)
	//	{
	//		CurrentState = REPEL;
	//	}

	//	CurrentState = ATTACK;
	//}
	//else
	//{
	//	CurrentState = IDLE;
	//}

	//if (CurrentState == IDLE)
	//{
	//	
	//}

	//else if (CurrentState == ATTACK)
	//{
	//	if (hero_x > pos_x)
	//	{
	//		pos_x = pos_x + 2;
	//	}
	//	else
	//	{
	//		pos_x = pos_x - 2;
	//	}
	//}

	//else if (CurrentState == REPEL)
	//{
	//	if (hero_x > pos_x)
	//	{	
	//		pos_x = pos_x -2;
	//	}
	//	else 
	//	{
	//		pos_x = pos_x + 2;
	//	}
	//}
}

void CZombies::update(int herox, int heroy)
{
	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX(), GetY());

	Vector3D<float> theDiff(HeroPos -  ZombiePos);

	theDiff.Normalize();
	vel += theDiff;
	
	pos.Set(GetX(),GetY());
	pos += vel;

	Set_X(pos.x);
	Set_Y(pos.y);
}

void CZombies::render(int mapOffset_x, int mapOffset_y)
{	
	//Zombies
	cout << "zombies" << endl;
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

