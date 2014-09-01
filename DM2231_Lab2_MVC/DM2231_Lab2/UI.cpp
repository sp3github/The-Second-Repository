#include "UI.h"
#include <stdio.h>

UI::UI(void)
{
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;
}


UI::~UI(void)
{
}
GLvoid UI::printw(float x, float y, float z,const GLuint &base, char *fmt, ...)					// Custom GL "Print" Routine
{
	glPushMatrix();
	glRasterPos3f (x, y, z);
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
	glPopMatrix();
}
void UI::RenderUI(StateType States, const GLuint&base)
{
	switch(States)
	{
	case LEVEL:
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			printw(26.0f, 86.0f, 0.0f, base,"HP: ");
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINE_STRIP);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(170.0f, 61.0f);
			glVertex2f(70.0f, 61.0f);

			glVertex2f(70.0f, 61.0f);
			glVertex2f(70.0f, 91.0f);

			glVertex2f(170.0f, 91.0f);
			glVertex2f(70.0f, 91.0f);

			glVertex2f(170.0f, 91.0f);
			glVertex2f(170.0f, 61.0f);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2f(71.0f, 62.0f);
			glVertex2f(169.0f*PlayerHP, 62.0f);
			glVertex2f(169.0f*PlayerHP, 91.0f);
			glVertex2f(71.0f, 91.0f);
		glEnd();
		glColor3f(1.0f, 1.0f, 1.0f);
		glPopMatrix();
		
		break;

	case STARTSCREEN:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.menuTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		break;

	case SUBPAGE:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.subpageTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		break;

	case CREDIT:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.creditTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		break;

	case WIN:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.winTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		break;

	case DEFEAT:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.defeatTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();

		break;

	case SHOP:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.shopTexture[0].texID);
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
				glEnd();
			glPopMatrix();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		break;

	default:
		break;
	}
}

void UI::SetHP(float currentHP, float maxHP)
{
	this->PlayerHP = currentHP/maxHP;
}

float UI::GetHP(void)
{
	return PlayerHP;
}