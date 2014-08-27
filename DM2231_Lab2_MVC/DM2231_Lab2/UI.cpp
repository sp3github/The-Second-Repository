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
	case PAUSE:
		break;
	case LEVEL:
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture.levelTexture[0].texID);
			glPushMatrix();
				glBegin(GL_QUADS);
					glTexCoord2f(0,0); glVertex2f(0, 600);
					glTexCoord2f(1,0); glVertex2f(800, 600);
					glTexCoord2f(1,1); glVertex2f(800, 0);
					glTexCoord2f(0,1); glVertex2f(0, 0);
			glPopMatrix();
			glDisable(GL_BLEND);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
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

		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			printw(370.0f, 250.0f, 0.0f, "PLAY");
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINE_STRIP);
			glColor3f(1.0f, 1.0f, 1.0f);
			
			// Top line of the box
			glVertex2f(450.0f, 220.0f);
			glVertex2f(350.0f, 220.0f);
			
			// Left line of the box
			glVertex2f(350.0f, 220.0f);
			glVertex2f(350.0f, 260.0f);

			// Bottom line of the box
			glVertex2f(350.0f, 260.0f);
			glVertex2f(450.0f, 260.0f);

			// Right line of the box
			glVertex2f(450.0f, 220.0f);
			glVertex2f(450.0f, 260.0f);
		glEnd();
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();
		
		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			printw(372.0f, 300.0f, 0.0f, "EXIT");
		glColor3f(0.0f , 0.0f ,0.0f);
		glPopMatrix();

		glPushMatrix();
		glBegin(GL_LINE_STRIP);
			glColor3f(1.0f, 1.0f, 1.0f);
			
			// Top line of the box
			glVertex2f(450.0f, 270.0f);
			glVertex2f(350.0f, 270.0f);
			
			// Left line of the box
			glVertex2f(350.0f, 270.0f);
			glVertex2f(350.0f, 310.0f);

			// Bottom line of the box
			glVertex2f(350.0f, 310.0f);
			glVertex2f(450.0f, 310.0f);

			// Right line of the box
			glVertex2f(450.0f, 270.0f);
			glVertex2f(450.0f, 310.0f);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);
		glPopMatrix();
		break;

	case SUBPAGE:
		glPushMatrix();
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
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		break;
	case ITEM:
		break;
	case VICTORY:
		break;
	case DEFEAT:
		break;
	case WINLEVEL:
		break;
	case BET:
		break;
	default:
		break;
	}
}

int UI::DetermineState(int choice)
{
	return 0;
}

void UI::Click(void)
{
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