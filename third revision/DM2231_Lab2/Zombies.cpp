#include "Zombies.h"

CZombies::CZombies(void)
: CurrentState(0)
, IDLE(0)
, ATTACK(0)
, REPEL(0)
, hero_x(0)
, hero_y(0)
, i(0)
{
	Set_X(rand()% 800);
	Set_Y(rand()% 600);

	vel.Set(10,10,10);
}

CZombies::~CZombies(void)
{
}

//Overloaded Constructor
//CZombies::CZombies( unsigned int w, unsigned int a, unsigned int d, int h, int st, float spd)
//{
//	walk = w;
//	attack = a;
//	die = d;
//	health = h;
//	moneysteal = st;
//	speed = spd;
//
//	iswalk = true;
//	isattack = false;
//	isdead = false;
//}

bool CZombies::ChangeState(const int newState)
{
	return false;
}

void CZombies::deceasingHealth(int num)
{
	health = num;
}
int CZombies::getHealth()
{
	return health;
}

int CZombies::getMoneySteal()
{
	return moneysteal;
}
bool CZombies::isDead()
{
	return isdead;
}

int CZombies::CalculateDistance(const int hero_x, const int hero_y)
{
	//return ( (hero_x - GetX()) * (hero_x - GetX()) + (hero_x - GetY()) * (hero_x - GetY()));
	return false;
}

void CZombies::Update()
{

	cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;
	if (hero_x < 0)
	{
		cout << "kidhasuidasiodasdsdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdasdawd" << endl;
	}
}

void CZombies::update(int herox, int heroy)
{
	Vector3D<float> HeroPos (herox,heroy);
	Vector3D<float> ZombiePos(herox, heroy);

	Vector3D<float> theDiff(HeroPos - ZombiePos);

	theDiff.Normalize();
	vel += theDiff;
	
	pos.Set(GetX(),GetY());
	pos += vel;

}


void CZombies::render()
{	

//	if (i < 10){
		// int x = rand()% 100;
		 //srand(time(NULL));
		//int y = rand()% 300;

		//cout << "ZOMBIE" << endl;
		int tile_size = 24;
		//Zombies
		glPushMatrix();
		glTranslatef(GetX(), GetY(), 0);
		glEnable(GL_TEXTURE_2D);		
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
		glTexCoord2f(1,1); glVertex2f(0,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		/*glPushMatrix();
		glTranslatef(300, 200, 0);
		glEnable(GL_TEXTURE_2D);		
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
		glTexCoord2f(1,1); glVertex2f(0,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 100, 0);
		glEnable(GL_TEXTURE_2D);		
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
		glTexCoord2f(1,1); glVertex2f(0,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(200, 300, 0);
		glEnable(GL_TEXTURE_2D);		
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex2f(0,0);
		glTexCoord2f(1,0); glVertex2f(tile_size,tile_size);
		glTexCoord2f(1,1); glVertex2f(0,tile_size);
		glTexCoord2f(0,1); glVertex2f(tile_size,0);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();*/
		
	//}
}

void CZombies::drawzombie(int x, int y)
{
	
		
	
}

