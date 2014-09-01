#include "UI.h"
#include <stdio.h>

UI::UI(void)
{
	font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	//theTexture=new loadTGA;
}


UI::~UI(void)
{
}

void UI::RenderUI(StateType States)
{
	switch(States)
	{
	case LEVEL:
		//glPushMatrix();
		//	glColor3f(1.0f , 1.0f, 1.0f);
		//	glEnable(GL_TEXTURE_2D);
		//	glEnable(GL_BLEND);
		//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//	glBindTexture(GL_TEXTURE_2D, theTexture.levelTexture[0].texID);
		//	glPushMatrix();
		//		glBegin(GL_QUADS);
		//			glTexCoord2f(0,0); glVertex2f(0, 600);
		//			glTexCoord2f(1,0); glVertex2f(800, 600);
		//			glTexCoord2f(1,1); glVertex2f(800, 0);
		//			glTexCoord2f(0,1); glVertex2f(0, 0);
		//	glPopMatrix();
		//	glDisable(GL_BLEND);
		//	glDisable(GL_TEXTURE_2D);
		//glColor3f(0.0f , 0.0f ,0.0f);
		//glPopMatrix();

		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			printw(26.0f, 86.0f, 0.0f, "HP: ");
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.subpageTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.creditTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.winTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.defeatTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
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
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.shopTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
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

void UI::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}

void UI::SetHP(float currentHP, float maxHP)
{
	this->PlayerHP = currentHP/maxHP;
}

float UI::GetHP(void)
{
	return PlayerHP;
}