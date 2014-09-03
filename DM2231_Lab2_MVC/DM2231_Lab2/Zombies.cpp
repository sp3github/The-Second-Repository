
#include "Zombies.h"

CZombies::CZombies(void)
: CurrentState(0)
, IDLE(0)
, ATTACK(0)
, REPEL(0)
, hero_x(0)
, hero_y(0)
{

	vel.Set(0.5,0.5,0.0);
	movementspeed = 100;
	pos.Set(GetX(), GetY());
	Timer = mvcTime::getInstance();
	TimeIndex = Timer->insertNewTime(50);
	bounce = false;
	Collided = false;
	
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
			Collided = false;
		}
		else
		{
			pos += BounceDir * dt;
			Set_X(pos.x);
			Set_Y(pos.y);
			Collided = true;
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
}

void CZombies::render(int mapOffset_x, int mapOffset_y)
{	

	glPushMatrix();
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
	glEnable(GL_TEXTURE_2D);		
	glColor3f(0,1,0);
	glBindTexture(GL_TEXTURE_2D, zombieTexture[1].texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(0,0);
	glTexCoord2f(1,1); glVertex2f(0,tile_size);
	glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
	glTexCoord2f(0,1); glVertex2f(tile_size,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void  CZombies::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	switch (other.ID)
	{

	case ZOMBIE:
		{
			if(!Collided)
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
				Collided = true;
			}
			break;

		}
	case PLAYER:
		{
			other.CollisionEvent(*this,theArray);
			break;
		}
	case BUILDING:
		{

			bounce = true;
			BounceDir = ((pos) - (Vector3D<float>(GetX(),GetY()))).Normalize() * movementspeed;
		
			Timer->resetTime(TimeIndex);
			Timer->changeLimit(TimeIndex, 500);
			break;
		}
	default:
		break;
	}
}

void CZombies::setZombie(ZombieStates zombieState)
{
	//switch (zombieState)
	//{
	//case normal:
	//	{
	//	
	//	}
	//	break;
	//}

	//case fast:
	//	{
	//	
	//	}
	//	break;

	//	case slow :
	//	{
	//	}
	//	break;
}
