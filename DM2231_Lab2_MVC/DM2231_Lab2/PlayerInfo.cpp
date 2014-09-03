#include "PlayerInfo.h"
#include <iostream>
#include "Zombies.h"

CPlayerInfo::CPlayerInfo(void)
{
	Init();
}

CPlayerInfo::~CPlayerInfo(void)
{

}

// Initialise this class instance
void CPlayerInfo::Init(void)
{
	heroAnimationCounter = 0;
	movementspeed = 5;
	HeroRotation = 0;
	tile_size = 24;

	hp = 100;

	time = mvcTime::getInstance();
	index = time->insertNewTime(5000);
	time->setActive(false,index);
}

/****************************************************************************************************
   Draw the hero
 ****************************************************************************************************/
GLvoid CPlayerInfo::printw(float x, float y, float z,const GLuint &base,const char *fmt, ...)					// Custom GL "Print" Routine
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
void CPlayerInfo::GetBase(const GLuint &base)
{
	this->base = base;
}
void CPlayerInfo::render(int mapOffset_x, int mapOffset_y) 
{	

	glPushMatrix();
	
	glTranslatef(static_cast<float>(GetX()), static_cast<float>(GetY()), 0);
	glTranslatef(static_cast<float>(tile_size * 0.5), static_cast<float>(tile_size * 0.5),0);
	glRotatef(HeroRotation,0,0,1);
	glTranslatef(static_cast<float>(-tile_size * 0.5), static_cast<float>(-tile_size * 0.5), 0);
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3f(1,0,0);
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

	glPushMatrix();
	glColor3f(1,0,0);
	printw(GetX()-25,GetY(),0,base,playername.c_str());
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
}

void CPlayerInfo::update(float dt)
{
	if(time->testTime(index))
	{
		movementspeed=5;
		time->setActive(false,index);

	}
}

void CPlayerInfo::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	switch(other.ID)
	{
	case HEALTH:
		{
			this->hp += 10;
			if(this->hp < 0)
			{
				this->hp = 0;
			}
			else if(this->hp > 100)
			{
				this->hp = 100;
			}

			other.Destroy = true;
		}
		break;
	case AMMO:
		{
			//this->ammo += 6;

			//if(this->ammo > 36)
			//{
			//	this->ammo = 36;
			//}

			other.Destroy = true;
		}
		break;
	case SLOWDOWN:
		{
			movementspeed = 15;
			time->setActive(true,index);
			

			other.Destroy = true;
		}
		break;
	case ZOMBIE:
		{
			this->hp -= 5;
			if(this->hp < 0)
				hp = 0;
			cout<<"HEALTH:"<<this->hp<<endl;

			CZombies * zombie;
			zombie = (dynamic_cast<CZombies*>(&other));

			zombie->bounce = true;
			zombie->BounceDir = ((zombie->pos) - (Vector3D<float>(GetX(),GetY()))).Normalize() * zombie->movementspeed;
		
			zombie->Timer->resetTime(zombie->TimeIndex);
			zombie->Timer->changeLimit(zombie->TimeIndex, 500);
		}
		break;
	case BUILDING:
		{
			
			break;
		}
	default:
			break;
	}
}