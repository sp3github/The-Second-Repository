#include "PlayerInfo.h"
#include <iostream>

CPlayerInfo::CPlayerInfo(void)
{
	m_iTileSize = 24;
	heroAnimationCounter = 0;
	movementspeed = 5;
	HeroRotation = 0;
	tile_size = 24;
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
void CPlayerInfo::render(void) {
	glPushMatrix();
	glTranslatef(GetX(), GetY(), 0);
	glTranslatef(m_iTileSize/2, m_iTileSize/2,0);
	glRotatef(HeroRotation,0,0,1);
	glTranslatef(-m_iTileSize / 2, -m_iTileSize / 2, 0);
	//glTranslatef(-20, -20,0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glRotatef(HeroRotation,0,0,1);

	glColor3f(1,0,0);
	//glBindTexture(GL_TEXTURE_2D, HeroTexture[1].texID);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25 * heroAnimationCounter, 1); glVertex2f(0, 0);
	glTexCoord2f(0.25 * heroAnimationCounter, 0); glVertex2f(0, m_iTileSize);
	glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 0); glVertex2f(m_iTileSize, m_iTileSize);
	glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 1); glVertex2f(m_iTileSize, 0);
	glEnd();



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
	if (GetX() < leftBorder)
	{
		Set_X(leftBorder);
		mapOffset_x =  mapOffset_x - (int) (movementspeed * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
		//cout<<"MAPOFFSET_X "<<mapOffset_x<<endl;
	}
	else if (GetX() > rightBorder)
	{
		Set_X(rightBorder);
		mapOffset_x = mapOffset_x + (int)(movementspeed * timeDiff);
		if (mapOffset_x > 800)	// This must be changed to soft-coded
			mapOffset_x = 800;
		//cout<<"MAPOFFSET_X "<<mapOffset_x<<endl;
	}

	if (GetY() < topBorder)
	{
		Set_Y(topBorder);
		mapOffset_y =  mapOffset_y - (int) (movementspeed * timeDiff);
		if (mapOffset_y < 0)
			mapOffset_y = 0;
	}
	else if (GetY() > bottomBorder)
	{
		Set_Y( bottomBorder);
		mapOffset_y = mapOffset_y + (int)(movementspeed * timeDiff);
		if (mapOffset_y > 600)	// This must be changed to soft-coded
			mapOffset_y = 600;
	}
}

void CPlayerInfo::moveMeUpDown(bool mode, float timeDiff, float movementspeed)
{
	// Check if the character is at a ladder. Return if not.
	if (mode)
	{
		Set_Y( GetY() - (int) (movementspeed * timeDiff) );
	}
	else
	{
		Set_Y( GetY() + (int) (movementspeed * timeDiff) );
	}
}

void CPlayerInfo::moveMeLeftRight(bool mode, float timeDiff, float movementspeed)
{
	if (mode)
	{
		
 		Set_X( GetX() - (int) (movementspeed * timeDiff) );
		SetAnimationInvert( true );
		SetAnimationCounter( GetAnimationCounter() - 1);
		if (GetAnimationCounter()==0)
			SetAnimationCounter( 3 );
	}
	else
	{
		
		Set_X( GetX() + (int) (movementspeed * timeDiff) );
		SetAnimationInvert( false );
		SetAnimationCounter( GetAnimationCounter() + 1);
		if (GetAnimationCounter() > 3)
			SetAnimationCounter( 0 );
	}
}

void CPlayerInfo::update()
{

}

bool CPlayerInfo::CollisionEvent(CEntity &other)
{
	switch(other.ID)
	{
	case HEALTH:

		break;
	}
	return false;
}