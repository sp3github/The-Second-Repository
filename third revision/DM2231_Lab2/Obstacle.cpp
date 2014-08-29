#include "Obstacle.h"

CObstacle::CObstacle(void)
{
}

CObstacle::~CObstacle(void)
{
}

CObstacle::CObstacle(int zc, int mzc, bool sr)
{
	spawnrate = sr;
	zombiecount = zc;
	maxzombiecount = mzc; 
}

int CObstacle::getZombiecount()
{
	return zombiecount;
}

void CObstacle::Spawn()
{

}

void CObstacle::renderObstacle()
{
	cout << "OBSTACLE" << endl;
	int tile_size = 24;
	glPushMatrix();
		glTranslatef(500,300, 0);
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

void CObstacle::UpdateObstacle()
{

} 