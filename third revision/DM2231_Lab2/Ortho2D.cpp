#include "Ortho2D.h"


Ortho2D::Ortho2D(void)
{
}


Ortho2D::~Ortho2D(void)
{
}

void Ortho2D::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, 800, 600, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
	}
}