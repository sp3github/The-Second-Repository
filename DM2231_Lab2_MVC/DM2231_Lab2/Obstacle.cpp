#include "Obstacle.h"

CObstacle::CObstacle(void)
{
	spawn = false;
	maxzombiecount = 5;

	Set_X(rand()% 800);
	Set_Y(rand()% 600);  
}

CObstacle::~CObstacle(void)
{
}

void CObstacle::render(int mapOffset_x, int mapOffset_y)
{	
	cout << "OBSTACLE" << endl;
	int tile_size = 24;
	glPushMatrix();
	glTranslatef(GetX()- mapOffset_x,GetY() - mapOffset_y, 0);
		glEnable(GL_TEXTURE_2D);
		glScalef(5,5,0);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(0,tile_size);
		glTexCoord2f(1,1); glVertex2f(tile_size,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void CObstacle::update()
{
	cout << "" << endl;
	if (zombiecount <= 0)
	{
		zombiecount = 0;

		if (zombiecount == 0)
		{
			cout << "AAAAAAAAAAAAAAAAHHHHHHHHHHHHHHHH" << endl;
			zombiecount++;
		}
	}
	if (zombiecount >= 11)
	{
		zombiecount = 11;
		
		if (zombiecount == 11)
		{
			cout << "OH NOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;
		}
	}
	cout << "ZOMBIE_COUNT: " << zombiecount << endl;
}

int CObstacle::getZombieCount()
{
	return zombiecount;
}

void CObstacle::setZombieCount(int z)
{
	zombiecount = z;
}