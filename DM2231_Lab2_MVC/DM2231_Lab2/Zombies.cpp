
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

	vel.Set(0.5,0.5,0.0);
	movementspeed = 0;
	pos.Set(GetX(), GetY());
	Timer = mvcTime::getInstance();
	TimeIndex = Timer->insertNewTime(50);
	bounce = false;

	
	zombie = 0;
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


void CZombies::setStats(int health, int moneysteal)
{
	health = 10;
	moneysteal = 20;

}
void CZombies::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
{

	if (bounce)
	{
		if (Timer->testTime(TimeIndex))
		{
			bounce = false;
		}
		else
		{
			pos += BounceDir * dt;
			Set_X(pos.x);
			Set_Y(pos.y);
		}
	}
	else
	{
		Vector3D<float> HeroPos(herox, heroy);
		Vector3D<float> ZombiePos(GetX() - mapOffset_x, GetY() - mapOffset_y);

		Vector3D<float> theDiff((HeroPos)-ZombiePos);

		if (theDiff.Magnitude() > 0.5)
		{
			theDiff.Normalize();

			if (movementspeed < 250)
				movementspeed += 100 * dt;

			vel = theDiff * movementspeed;


			pos += vel * dt;

			Set_X(pos.x);
			Set_Y(pos.y);
		}
	}

	Vector3D<float> vel;
	Vector3D<float> pos;

	vel.Set(0.5,0.5,0.5);

	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX(), GetY());

	Vector3D<float> theDiff((HeroPos * dt) - ZombiePos*dt);

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

	cout << "NORMAL" << endl;

	glPushMatrix();
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
	glEnable(GL_TEXTURE_2D);		
	glColor3f(0,1,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(0,0);
	glTexCoord2f(1,1); glVertex2f(0,tile_size);
	glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
	glTexCoord2f(0,1); glVertex2f(tile_size,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

vector<CEntity*>::iterator  CZombies::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	switch (other.ID)
	{

	case ZOMBIE:
		{
			CZombies * zombie;
			zombie = (dynamic_cast<CZombies*>(&other));

			bounce = true;
			zombie->bounce = true;

			this->BounceDir = ((this->pos) - (zombie->pos)).Normalize() * movementspeed;
			zombie->BounceDir = ((zombie->pos) - (this->pos)).Normalize() * zombie->movementspeed;
		
			Timer->resetTime(TimeIndex);
			zombie->Timer->resetTime(zombie->TimeIndex);
			Timer->changeLimit(TimeIndex, 50);
			zombie->Timer->changeLimit(zombie->TimeIndex, 50);

			break;

		}
	default:
		break;
	}
	for (auto it = theArray.begin(); it != theArray.end(); it++)
			{
				CEntity *go = NULL;
				go = (*it);
				if (go == this)
				{
					return it + 1;
				}

			}
}




void CZombies::setZombie(ZombieStates zombieState)
{
	
}
