#include "PlayerInfo.h"
#include <iostream>

CPlayerInfo::CPlayerInfo(void)
{
	m_iTileSize = 24;
	heroAnimationCounter = 0;
	movementspeed = 5;
}

CPlayerInfo::~CPlayerInfo(void)
{
}

// Initialise this class instance
void CPlayerInfo::Init(void)
{
}

/****************************************************************************************************
   Draw the hero
 ****************************************************************************************************/
void CPlayerInfo::RenderHero(void) {
	glPushMatrix();
	glTranslatef(hero_x, hero_y, 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (heroAnimationInvert == false)
		{	
			glBindTexture(GL_TEXTURE_2D, HeroTexture[1].texID);
			glBegin(GL_QUADS);
 
			glTexCoord2f(0.25 * heroAnimationCounter, 1); glVertex2f(0, 0);
			glTexCoord2f(0.25 * heroAnimationCounter, 0); glVertex2f(0, m_iTileSize);
			glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 0); glVertex2f(m_iTileSize, m_iTileSize);
			glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 1); glVertex2f(m_iTileSize, 0);
			glEnd();
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, HeroTexture[1].texID);
			glBegin(GL_QUADS);
			glTexCoord2f(0.25 * heroAnimationCounter + 0.24,1); glVertex2f(0,0);
			glTexCoord2f(0.25 * heroAnimationCounter + 0.24,0); glVertex2f(0,m_iTileSize);
			glTexCoord2f(0.25 * heroAnimationCounter,0); glVertex2f(m_iTileSize,m_iTileSize);
			glTexCoord2f(0.25 * heroAnimationCounter,1); glVertex2f(m_iTileSize,0);
			glEnd();
		}

	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();
}

// Set Animation Invert status of the player
void CPlayerInfo::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}
// Get Animation Invert status of the player
bool CPlayerInfo::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}

// Set Animation Counter of the player
void CPlayerInfo::SetAnimationCounter(int heroAnimationCounter)
{
	this->heroAnimationCounter = heroAnimationCounter;
}
// Get Animation Counter of the player
int CPlayerInfo::GetAnimationCounter(void)
{
	return heroAnimationCounter;
}

// Constrain the position of the Hero to within the border
void CPlayerInfo::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff,
								  int& mapOffset_x, int& mapOffset_y)
{
	if (hero_x < leftBorder)
	{
		hero_x = leftBorder;
		mapOffset_x =  mapOffset_x - (int) (movementspeed * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (hero_x > rightBorder)
	{
		hero_x = rightBorder;
		mapOffset_x = mapOffset_x + (int)(movementspeed * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
	}

	if (hero_y < topBorder)
		hero_y = topBorder;
	else if (hero_y > bottomBorder)
		hero_y = bottomBorder;
}