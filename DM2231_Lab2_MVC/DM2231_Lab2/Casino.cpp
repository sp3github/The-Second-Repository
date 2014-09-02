#include "Casino.h"


Casino::Casino(void)
{
	tile_size = 80;
	maxzombiecount = 5;
}


Casino::~Casino(void)
{
}

void Casino::Spawn()
{
	//theArrayofEntities->push_back(theFactory->Create(ZOMBIE));
	//theArrayofEntities->back()->SetPos(GetX(), GetY());
}

void Casino::render(int mapOffset_x, int mapOffset_y)
{	
	cout << "CASINO" << endl; 
	glPushMatrix();
	glTranslatef(GetX()- mapOffset_x,GetY() - mapOffset_y, 0);
		glEnable(GL_TEXTURE_2D);
		glColor3f(1,0,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(0,tile_size);
		glTexCoord2f(1,1); glVertex2f(tile_size,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Casino::update(float dt)
{
	if (maxzombiecount < 5)
	{
		Spawn();
	}
}