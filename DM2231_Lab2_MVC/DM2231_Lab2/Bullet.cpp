#include "bullet.h"


bullet::bullet()
{
	tile_size = 10;
}


bullet::~bullet()
{
}



bool bullet::SetAngle(float HeroRotation)
{
	this->HeroRotationRad = static_cast<float>(HeroRotation * 3.1415 / 180);
	return true;
}

bool bullet::SetPower(int power)
{
	this->power = power;
	this->movementspeed = power;
	return true;
}


void bullet::render(int mapOffset_x, int mapOffset_y)
{
	glPushMatrix();
	glTranslatef(GetX(), GetY(), 0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1, 0, 0);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(0, 0);
	glTexCoord2f(0, 0); glVertex2f(0, tile_size);
	glTexCoord2f(1, 0); glVertex2f(tile_size, tile_size);
	glTexCoord2f(1, 1); glVertex2f(tile_size, 0);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void bullet::update(float dt)
{
	pos.Set(GetX(),GetY());


	vel.Set(cos(HeroRotationRad), sin(HeroRotationRad));
	vel.Normalize();

	pos += vel * power * dt;

	Set_X(pos.x);
	Set_Y(pos.y);
}

void bullet::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	switch (other.ID)
	{
	case ZOMBIE:
		{
			other.hp -= power * 0.01;//Effect

			this->Destroy = true;

			if(other.hp <= 0)
			{
				for (auto it = theArray.begin(); it != theArray.end(); it++)
				{
					if ((*it)->ID == PLAYER)
					{
						CPlayerInfo * theHero;
						theHero = dynamic_cast<CPlayerInfo*>(*it);
						theHero->money.AddMoney(10);
					}
				}
				other.Destroy = true;
			}
		}
	case BUILDING:
		{
			this->Destroy = true;
		}
	default:
		break;
	}
}