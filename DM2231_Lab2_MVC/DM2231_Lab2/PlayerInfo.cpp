#include "PlayerInfo.h"
#include <iostream>

CPlayerInfo::CPlayerInfo(void)
{
	heroAnimationCounter = 0;
	movementspeed = 5;
	HeroRotation = 0;

	tile_size = 24;

	hp = 0;
	ammo = 0;
	slow = false;
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
void CPlayerInfo::render(int mapOffset_x, int mapOffset_y) {
	glPushMatrix();
	glTranslatef(GetX(), GetY(), 0);
	glTranslatef(tile_size/2, tile_size/2,0);
	glRotatef(HeroRotation,0,0,1);
	glTranslatef(-tile_size / 2, -tile_size / 2, 0);
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
	glTexCoord2f(0.25 * heroAnimationCounter, 0); glVertex2f(0, tile_size);
	glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 0); glVertex2f(tile_size, tile_size);
	glTexCoord2f(0.25 * heroAnimationCounter + 0.24, 1); glVertex2f(tile_size, 0);
	glEnd();

	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glPopMatrix();


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
void CPlayerInfo::ConstrainHero( const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, const int LsoftBorder, const int RsoftBorder, const int TsoftBorder, const int BsoftBorder, float timeDiff, int& mapOffset_x, int& mapOffset_y, int mapheight, int mapwidth)
{
	if (GetX() < leftBorder) 
	{ 
		Set_X(leftBorder);
		mapOffset_x = mapOffset_x - (int) (movementspeed * timeDiff);
		if (mapOffset_x < 0) mapOffset_x = 0;
	} 
	else if(GetX()<LsoftBorder&&mapOffset_x>0)
	{ 
		Set_X(LsoftBorder);
		mapOffset_x = mapOffset_x - (int) (movementspeed * timeDiff); 
		if (mapOffset_x < 0) 
			mapOffset_x = 0; 
	} 
	else if
		(GetX() > rightBorder) 
	{ 
		Set_X(rightBorder) ; 
		mapOffset_x = mapOffset_x + (int) (movementspeed * timeDiff); 
		if (mapOffset_x > mapwidth) // This must be changed to soft-coded 
			mapOffset_x = mapwidth ; 
	} 
	else if(GetX()>RsoftBorder&&mapOffset_x<mapwidth) 
	{
		Set_X(RsoftBorder);
		mapOffset_x = mapOffset_x + (int) (movementspeed * timeDiff); 
		if (mapOffset_x > mapwidth) 
			mapOffset_x = mapwidth; 
	}


	if (GetY() < topBorder)
	{
		Set_Y(topBorder);
		mapOffset_y =  mapOffset_y - (int) (movementspeed * timeDiff);
		if (mapOffset_y < 0)
			mapOffset_y = 0;
		cout<<"MAPOFFSET_Y "<<mapOffset_y<<endl;
	}
	else if (GetY() > bottomBorder)
	{
		Set_Y( bottomBorder);
		mapOffset_y = mapOffset_y + (int)(movementspeed * timeDiff);
		if (mapOffset_y > 600)	// This must be changed to soft-coded
			mapOffset_y = 600;
		cout<<"MAPOFFSET_Y "<<mapOffset_y<<endl;
	}
	if (GetY() < topBorder) 
	{ 
		Set_Y(leftBorder);
		mapOffset_y = mapOffset_y - (int) (movementspeed * timeDiff);
		if (mapOffset_y < 0) mapOffset_y = 0;
	} 
	else if(GetY()<TsoftBorder&&mapOffset_y>0)
	{ 
		Set_Y(TsoftBorder);
		mapOffset_y = mapOffset_y - (int) (movementspeed * timeDiff); 
		if (mapOffset_y < 0) 
			mapOffset_y = 0; 
	} 
	else if
		(GetY() > bottomBorder) 
	{ 
		Set_Y(bottomBorder) ; 
		mapOffset_y = mapOffset_y + (int) (movementspeed * timeDiff); 
		if (mapOffset_y > mapheight) // This must be changed to soft-coded 
			mapOffset_y = mapheight ; 
	} 
	else if(GetY()>BsoftBorder&&mapOffset_y< mapheight) 
	{
		Set_Y(BsoftBorder);
		mapOffset_y = mapOffset_y + (int) (movementspeed * timeDiff); 
		if (mapOffset_y > mapheight) 
			mapOffset_y = mapheight; 
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
	cout<<"My Y Pos is: "<<GetY()<<endl;
}

void CPlayerInfo::moveMeLeftRight(bool mode, float timeDiff, float movementspeed)
{
	if (mode)
	{
		
 		Set_X( GetX() - (int) (movementspeed * timeDiff) );
		SetAnimationCounter( GetAnimationCounter() - 1);
		if (GetAnimationCounter()==0)
			SetAnimationCounter( 3 );
	}
	else
	{
		
		Set_X( GetX() + (int) (movementspeed * timeDiff) );
		SetAnimationCounter( GetAnimationCounter() + 1);
		if (GetAnimationCounter() > 3)
			SetAnimationCounter( 0 );
	}
	cout<<"My X Pos is: "<<GetX()<<endl;
}

void CPlayerInfo::update()
{
	return;
}

bool CPlayerInfo::CollisionEvent(CEntity &other)
{
	switch(other.ID)
	{
	case HEALTH:
		{
			this->hp += 10;

			if(this->hp > 100)
			{
				this->hp = 100;
			}
		}
		break;
	case AMMO:
		{
			this->ammo += 6;

			if(this->ammo > 36)
			{
				this->ammo = 36;
			}
		}
		break;
	case SLOWDOWN:
		{
			this->slow = true;
		}
		break;
	}
	return false;


}