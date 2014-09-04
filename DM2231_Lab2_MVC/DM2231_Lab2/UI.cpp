#include "UI.h"
#include <stdio.h>

UI::UI(void)
{
}


UI::~UI(void)
{
}

GLvoid UI::printw(float x, float y, float z,const GLuint &base,const char *fmt, ...)					// Custom GL "Print" Routine
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
	case ENTERNAME:
		theSound.RenderSound(Sound::MENU);
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.nameTexture[0].texID);
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
	case STORYIN:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.storyTexture[0].texID);
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
	case LEVEL:
		//theSound.RenderSound(Sound::LEVEL);

		glPushMatrix();
			glColor3f(1.0f, 0.0f, 0.0f);
			printw(26.0f, 86.0f, 0.0f, base,"Hp: ");
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.f,0.f,0.f);
		printw(400,40,0,base,"Money: %.i",theHero->money.playerMoney);
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

		glPushMatrix();
			glColor3f(1,0,0);
			glTranslatef(650.0f, 70.0f, 0.0f);
			printw(0,0,0,base,"PISTOL AMMO: %i", theGun->bulletCount[0] + theGun->currentBullet[0]);
			glColor3f(1,1,1);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1,0,0);
			glTranslatef(650.0f, 140.0f, 0.0f);
			printw(0,0,0,base,"UZI AMMO: %i",theGun->bulletCount[1] + theGun->currentBullet[1]);
			glColor3f(1,1,1);
		glPopMatrix();
		
		glPushMatrix();
		glColor3f(1,0,0);
			glTranslatef(650.0f, 210.0f, 0.0f);
			printw(0,0,0,base,"SHOTGUN AMMO: %i",theGun->bulletCount[2] + theGun->currentBullet[2]);
			glColor3f(1,1,1);
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
				glBindTexture(GL_TEXTURE_2D, theTexture.gambledTexture[0].texID);
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
		theSound.RenderSound(Sound::SUBPAGE);
		
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
		theSound.RenderSound(Sound::SUBPAGE);

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
		theSound.RenderSound(Sound::SUBPAGE);

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
		theSound.RenderSound(Sound::SCORE);



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

		glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(450,550,0);
		printw(0,0,0,base,"Money to Risk: %i",atoi(theBet->AmounttoBet.c_str()));
		glPopMatrix();
		break;
	case SUBSHOP:
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
	case INS:
		glPushMatrix();
			glColor3f(1.0f , 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, theTexture.insTexture[0].texID);
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

void UI::SetGun(gun &theGun)
{
	this->theGun = &theGun;
}

void UI::SetPlayer(CPlayerInfo & theHero)
{
	this->theHero = &theHero;
}

void UI::SetBet(Bet &theBet)
{
	this->theBet = &theBet;
}