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
	srand(NULL);
	Set_X(rand()% 800);
	Set_Y(rand()% 600);  
	vel.Set(0.5,0.5,0.0);
	movementspeed = 1;
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
	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX() - mapOffset_x, GetY() - mapOffset_y);

	Vector3D<float> theDiff((HeroPos * dt) - ZombiePos*dt);

	if(theDiff.Magnitude() > 0.5)
	{
		theDiff.Normalize();
		
		//vel = vel.Cross(theDiff);
	//	vel += theDiff;

		pos.Set(GetX(),GetY());

		pos += vel;
		pos += theDiff;

		if (vel.x > 0.5)
			vel.x -= 0.5;
		else
		{
			vel.x = 0.5;
		}
		if (vel.y > 0.5)
			vel.y -= 0.5;
		else
		{
			vel.y = 0.5;
		}

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
	case HEALTH:
		{
			for (auto it = theArray.begin(); it != theArray.end();it++)
			{
				CEntity *go = NULL;
				go = (*it);
				if (go == &other)
				{
					return it + 1;
				}

			}
		}
	case ZOMBIE:
		{
			CZombies * zombie;
			zombie = (dynamic_cast<CZombies*>(&other));
			float m1 = 1;
			float m2 = 1;
			Vector3D<float> A = this->pos;
			Vector3D<float> B = zombie->pos;
			Vector3D<float> D = A - B;
			if (D != Vector3D<float>(0,0))
				D.Normalize();
			Vector3D<float> u1 = this->vel;
			Vector3D<float> u2 = zombie->vel;
			Vector3D<float> v1 = u1 - D * (2 * (u1 - u2).Dot(D) * m2 / (m1 + m2));
			Vector3D<float> v2 = u2 + D * (2 * (u1 - u2).Dot(D) * m1 / (m1 + m2));

			this->vel = v1 * - 3;
			zombie->vel = v2 * 3;

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
	default:
		break;
	}
}