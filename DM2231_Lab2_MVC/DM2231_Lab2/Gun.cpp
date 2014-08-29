#include "gun.h"
gun::gun()
{
	GunRenderOffset_x = 20;
	GunRenderOffset_y = 20;
	tile_size = 10;
	time = mvcTime::getInstance();
	index = time->insertNewTime(MilliSecondPerShot);
	SetGun(pistol);



}


gun::~gun()
{
}

void gun::render()
{
	glPushMatrix();
	glTranslatef(static_cast<float>(theHero->GetX() + GunRenderOffset_x), static_cast<float>(theHero->GetY() + tile_size * 0.5), 0);
	glTranslatef(static_cast<float>(tile_size * 0.5 - GunRenderOffset_x), static_cast<float>(tile_size * 0.5), 0);
	glRotatef(theHero->HeroRotation, 0, 0, 1);
	glTranslatef(-tile_size * 0.5 + GunRenderOffset_x, -tile_size * 0.5, 0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(0, 1, 1);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(0, 0);
	glTexCoord2f(0, 0); glVertex2f(0, static_cast<float>(tile_size));
	glTexCoord2f(1, 0); glVertex2f(static_cast<float>(tile_size), static_cast<float>(tile_size));
	glTexCoord2f(1, 1); glVertex2f(static_cast<float>(tile_size), 0);
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

bool gun::SetPlayer(CPlayerInfo &theHero)
{
	if (this->theHero = &theHero)
		return true;
	else
		return false;
}

void gun::FireGun()
{

	if (currentBullet > 0)
	{

		if (time->testTime(index))	//Count time
		{
			currentBullet -= 1;	//Take away one bullet
			//DO BULLET STUFF HERE
			theArrayofEntities->insert(theArrayofEntities->begin(),(theFactory->Create(BULLET)));
			theArrayofEntities->front()->SetPos(theHero->GetX(), theHero->GetY());
			thePointertoBullet = (dynamic_cast<bullet*> (theArrayofEntities->front()));
			thePointertoBullet->SetAngle(theHero->HeroRotation);
			thePointertoBullet->SetPower(power);
		}
		prevshot = currentshot;
	}

	if (currentBullet <= 0)	//AUTO RELOAD
	{
		currentreload = static_cast<float>(timeGetTime());
		if (reloadC == false){
			prevreload = currentreload;
			reloadC = true;
		}
		if (currentreload - prevreload >= reloadtime)
		{
			ReloadGun();
			reloadC = false;;
		}
	}
}

void gun::ReloadGun()
{
	if (bulletCount >= 0)	//CHECK IF YOU HAVE ENOUGH AMMO
	{

		if (currentBullet >= bulletCount)		//IF LESS BULLET THAN RELOADABLE COUNT, USE ALL BULLETS LEFT
		{
			currentBullet += bulletCount;
			bulletCount = 0;
		}
		else
		{
			bulletCount = bulletCount - (ReloadBullet - currentBullet);
			currentBullet = ReloadBullet;//ELSE SET CURRENT BULLET TO 30 AND MINUS OFF BULLET COUNT

		}
	}
}

void gun::SetGun(GunStates theState)
{
	switch (theState)
	{
	case pistol:
		bulletCount = 18;
		currentBullet = 15;
		ReloadBullet = 15;

		power = 1000;
		firing = false;
		prevshot = 0;
		currentshot = 0;
		currentreload = 0;
		prevreload = 0;
		reloadtime = 100;
		reloadC = false;

		MilliSecondPerShot = 400;

		totalbullet = bulletCount + currentBullet;

		StateNow = pistol;

		time->resetTime(index);//have a time reference
		time->changeLimit(index, MilliSecondPerShot);//reset time and change limit

		break;
	case uzi:
		bulletCount = 60;
		currentBullet = 30;
		ReloadBullet = 30;

		power = 2000;
		firing = false;
		prevshot = 0;
		currentshot = 0;
		currentreload = 0;
		prevreload = 0;
		reloadtime = 100;
		reloadC = false;

		MilliSecondPerShot = 150;

		totalbullet = bulletCount + currentBullet;
		StateNow = uzi;

		time->resetTime(index);//have a time reference
		time->changeLimit(index, MilliSecondPerShot);//reset time and change limit


		break;
	case shotgun:
		bulletCount = 9;
		currentBullet = 9;
		ReloadBullet = 9;

		power = 3000;
		firing = false;
		prevshot = 0;
		currentshot = 0;
		currentreload = 0;
		prevreload = 0;
		reloadtime = 100;
		reloadC = false;

		MilliSecondPerShot = 700;

		totalbullet = bulletCount + currentBullet;
		StateNow = shotgun;

		time->resetTime(index);//have a time reference
		time->changeLimit(index, MilliSecondPerShot);//reset time and change limit


		break;
	}
}

void gun::SetArray(vector<CEntity*> & theArrayofEntities)
{
	this->theArrayofEntities = &theArrayofEntities;
}

void gun::SetFactory(CEntityFactory & theFactory)
{
	this->theFactory = &theFactory;
}