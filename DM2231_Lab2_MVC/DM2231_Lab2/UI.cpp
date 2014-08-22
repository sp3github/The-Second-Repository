#include "UI.h"

UI::UI(void)
{
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
			glBindTexture(GL_TEXTURE_2D, theTexture->levelTexture[0].texID);
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
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture->menuTexture[0].texID);
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
	case SUBPAGE:
		glPushMatrix();
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, theTexture->subpageTexture[0].texID);
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
