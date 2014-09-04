#include "Ammo.h"


CAmmo::CAmmo(void)
{
}


CAmmo::~CAmmo(void)
{
}

void CAmmo::update(float dt)
{
}

void CAmmo::render(int mapOffset_x, int mapOffset_y)
{
	glPushMatrix();
		glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
		glEnable( GL_TEXTURE_2D );
		glEnable( GL_BLEND );
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glColor3f(0,0.5,1);

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