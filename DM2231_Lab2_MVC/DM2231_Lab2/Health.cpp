#include "Health.h"


CHealth::CHealth(void)
{
}


CHealth::~CHealth(void)
{
}

void CHealth::update()
{
}

void CHealth::render(int mapOffset_x, int mapOffset_y)
{
	glPushMatrix();
		glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glColor3f(1,0.5,1);
		glBindTexture(GL_TEXTURE_2D, tex.texID);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(0,tile_size);
		glTexCoord2f(1,1); glVertex2f(tile_size,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();

		glDisable( GL_BLEND );
		glDisable( GL_TEXTURE_2D );
	glPopMatrix();
}