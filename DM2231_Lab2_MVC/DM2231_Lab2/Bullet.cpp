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

vector<std::shared_ptr<CEntity>>::iterator bullet::CollisionEvent(CEntity &other, vector<std::shared_ptr<CEntity>> & theArray)
{
	switch (other.ID)
	{

	case HEALTH:
		{
			break;
		}
	case ZOMBIE:
		{
			other.hp -= power * 0.01;//Effect
			

			int Counter, index, bulletindex;
			vector<std::shared_ptr<CEntity>>::iterator it = theArray.begin();
			//Find the bullet and the other in the array.
			for (it = theArray.begin(), Counter = 0; it != theArray.end();it++, Counter++)
			{
				vector<std::shared_ptr<CEntity>> go;
				go = (*it);
				if (go == &other)
				{
					index = Counter;
				}
				if(go->ID == BULLET && go->GetX() == GetX() && go->GetY() == GetY())
				{
					bulletindex = Counter;
				}
			}

			//delete this;//Delete the bullet
			this->~bullet();
			theArray.erase(theArray.begin() + bulletindex);
			
			index -= 1;

			if(other.hp <= 0)
			{
				//delete &other;
				other.~CEntity();
				it = theArray.erase(theArray.begin() + index); //delete from array.
				
				return it;
			}
			
			it = theArray.begin() + index;
			return it;
			
		}
	case BUILDING:
		{
			int Counter, bulletindex;
			vector<std::shared_ptr<CEntity>>::iterator i;
			vector<std::shared_ptr<CEntity>>::iterator it;
			for (it = theArray.begin(), Counter = 0; it != theArray.end();it++, Counter++)
			{
				std::shared_ptr<CEntity> go= NULL;
				go = (*it);
				if(static_cast<shared_ptr<CEntity>>(this) == go)
				{
					bulletindex = Counter;
					break;
				}
				if(static_cast<shared_ptr<CEntity>>(&other) == go)
				{
					i = it;
				}
			}

			theArray.erase(theArray.begin() + bulletindex);
			this->~bullet();
			return i + 1;
		}
	default:
		break;
	}
	for (vector<std::shared_ptr<CEntity>>::iterator it = theArray.begin(); it != theArray.end();it++)
	{
		std::shared_ptr<CEntity> go = NULL;
		go = (*it);
		if (static_cast<shared_ptr<CEntity>>(&other) == go)
		{
			return it + 1;
		}

	}
}