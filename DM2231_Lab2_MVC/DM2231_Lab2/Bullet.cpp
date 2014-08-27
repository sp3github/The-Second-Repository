#include "Bullet.h"

Bullet::Bullet(void)
{
	canFire = false;
}

Bullet::~Bullet(void)
{


}

void Bullet::FireBullet(float x, float y)
{

	
}

void Bullet::render()
{

}

void Bullet::update()
{


	sx = x;
	sy = y;
}

void Bullet::Draw()
{
	int tile_size = 24;
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glTranslatef(sx,sy,0);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0);	glVertex2f(0,tile_size);
	glTexCoord2f(1,0);	glVertex2f(tile_size,tile_size);
	glTexCoord2f(1,1);	glVertex2f(tile_size,0);
	glTexCoord2f(0,1);	glVertex2f(0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();						
}

void Bullet::Tick()
{
	sy -= 0.06;

}