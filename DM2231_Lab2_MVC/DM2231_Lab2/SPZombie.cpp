#include "SPZombie.h"


SPZombie::SPZombie(void)
{
	tile_size = 24;
	vel.Set(0.5,0.5,0.0);
	movementspeed = 100;
	pos.Set(GetX(), GetY());
	Timer = mvcTime::getInstance();
	TimeIndex = Timer->insertNewTime(100);
	bounce = false;
	Collided = false;
	
	//zombie = 0;
}

SPZombie::~SPZombie(void)
{

}

void SPZombie::setPlayerName(string playername)
{
	 zombiename = playername ;
	cout <<   "Gambler's Name:" << zombiename <<  endl;
}

void SPZombie::getLevel(short level)
{
	this->level = level;
	cout << "Got It!!!!!!" << level << endl;
}

string SPZombie::getPlayerName()
{
	return playername;
}

GLvoid SPZombie::printw(float x, float y, float z,const GLuint &base,const char *fmt, ...)					// Custom GL "Print" Routine
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

void SPZombie::GetBase(const GLuint &base)
{
	this->base = base;
}

void SPZombie::render(int mapOffset_x, int mapOffset_y)
{
	glPushMatrix();
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
	glEnable(GL_TEXTURE_2D);		
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex2f(0,0);
	glTexCoord2f(1,1); glVertex2f(0,tile_size);
	glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
	glTexCoord2f(0,1); glVertex2f(tile_size,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1,0,0);
	glTranslatef(GetX() - mapOffset_x, GetY() - mapOffset_y, 0);
 	printw(0,0,0,base,zombiename.c_str());
	glPopMatrix();
}

void SPZombie::update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt)
{
	if (bounce)
	{
		if (Timer->testTime(TimeIndex))
		{
			bounce = false;
			Collided = false;
		}
		else
		{
			pos += BounceDir * dt;
			Set_X(pos.x);
			Set_Y(pos.y);
			Collided = true;
		}
	}
	else
	{
		Vector3D<float> HeroPos(herox, heroy);
		Vector3D<float> ZombiePos(GetX() - mapOffset_x, GetY() - mapOffset_y);

		Vector3D<float> theDiff((HeroPos)-ZombiePos);

		if (theDiff.Magnitude() > 0.5)
		{
			theDiff.Normalize();

			if (movementspeed < 250)
				movementspeed += 100 * dt;

			vel = theDiff * movementspeed;


			pos += vel * dt;

			Set_X(pos.x);
			Set_Y(pos.y);
		}
	}

	Vector3D<float> vel;
	Vector3D<float> pos;

	vel.Set(0.5,0.5,0.5);

	Vector3D<float> HeroPos(herox,heroy);
	Vector3D<float> ZombiePos(GetX(), GetY());

	Vector3D<float> theDiff((HeroPos * dt) - ZombiePos*dt);

	if(theDiff.Magnitude() > 0.5)
		theDiff.Normalize();
	vel += theDiff;
	
	pos.Set(GetX(),GetY());
	pos += vel;

	Set_X(pos.x);
	Set_Y(pos.y);
}

void  SPZombie::CollisionEvent(CEntity &other, vector<CEntity*> & theArray)
{
	switch (other.ID)
	{
	case SPZOMBIE:
		{
			if(!Collided)
			{
				SPZombie * spzombie;
				spzombie = (dynamic_cast<SPZombie*>(&other));

				bounce = true;
				spzombie->bounce = true;

				this->BounceDir = ((this->pos) - (spzombie->pos)).Normalize() * movementspeed;
				spzombie->BounceDir = ((spzombie->pos) - (this->pos)).Normalize() * spzombie->movementspeed;

				Timer->resetTime(TimeIndex);
				spzombie->Timer->resetTime(spzombie->TimeIndex);
				Timer->changeLimit(TimeIndex, 50);
				spzombie->Timer->changeLimit(spzombie->TimeIndex, 50);
				Collided = true;
			}
			break;
		}
	case PLAYER:
		{
			other.CollisionEvent(*this,theArray);
			break;
		}
	case BUILDING:
		{

			bounce = true;
			BounceDir = ((pos) - (Vector3D<float>(GetX(),GetY()))).Normalize() * movementspeed;
		
			Timer->resetTime(TimeIndex);
			Timer->changeLimit(TimeIndex, 500);
			break;
		}
	default:
		break;
	}
}
