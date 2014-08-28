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
	glColor3f(0, 1, 0);

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
	Vector3D<float> pos(GetX(),GetY());
	Vector3D<float> vel;

	vel.Set(cos(HeroRotationRad), sin(HeroRotationRad));
	vel.Normalize();


	pos += vel * power * dt;

	Set_X(pos.x);
	Set_Y(pos.y);
}

vector<CEntity*>::iterator bullet::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
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
	default:
		break;
	}
}