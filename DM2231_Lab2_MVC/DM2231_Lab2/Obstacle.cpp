#include "Obstacle.h"

CObstacle::CObstacle(void)
{
	zombiecount = 0;
	spawn = false;
	maxzombiecount = 5;

	Set_X(rand()% 800);
	Set_Y(rand()% 600);  
}

CObstacle::~CObstacle(void)
{
}

int CObstacle::getZombiecount()
{
	return zombiecount;
}

void CObstacle::render(int mapOffset_x, int mapOffset_y)
{	
	cout << "OBSTACLE" << endl;
	int tile_size = 24;
	glPushMatrix();
	glTranslatef(GetX()- mapOffset_x,GetY() - mapOffset_y, 0);
		glEnable(GL_TEXTURE_2D);
		glScalef(5,5,0);
		glColor3f(0,1,1);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(0,tile_size);
		glTexCoord2f(1,1); glVertex2f(tile_size,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void CObstacle::update(int ZombieCount)
{
//	Vector3D<float> ObstaclePos(ObstacleX, ObstacleY);
//	Vector3D<float> ZombiePos(GetX(), GetY());
//
//	//Vector3D<float> theDiff(HeroPos -  ZombiePos);
//
//	theDiff.Normalize();
//	vel += theDiff;
//	
//	pos.Set(GetX(),GetY());
//	pos += vel;
//
//	Set_X(pos.x);
//	Set_Y(pos.y);
//
}

bool CObstacle::Spawn()
{
	return true;
}