#include "SPZombie.h"


SPZombie::SPZombie(void)
{
	tile_size = 48;
}


SPZombie::~SPZombie(void)
{

}

void SPZombie::setPlayerName(string playername)
{
	playername = zombiename;
}

int SPZombie::getLevel(int level)
{
	return level;
}

void SPZombie::SpawnSP()
{
	
}

void SPZombie::render(int mapOffset_x, int mapOffset_y)
{
	cout << "SpecialZombie" << endl;

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

void SPZombie::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
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

	Vector3D<float> vel;
	Vector3D<float> pos;

	vel.Set(0.5,0.5,0.5);

	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX(), GetY());

	Vector3D<float> theDiff((HeroPos * dt) - ZombiePos*dt);

	if(theDiff.Magnitude() > 0.5)
		theDiff.Normalize();
	vel += theDiff;
	
	pos.Set(GetX(),GetY());
	pos += vel;

	Set_X(pos.x);
	Set_Y(pos.y);
}

void  SPZombie::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
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
	default:
		break;
	}
}