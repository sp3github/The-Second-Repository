#include "gun.h"
gun::gun()
{
	BulletState = 0;
	InitGun();

	GunRenderOffset_x = 20;
	GunRenderOffset_y = 20;
	tile_size = 10;
	time = mvcTime::getInstance();
	index = time->insertNewTime(MilliSecondPerShot[BulletState]);

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
	glColor3f(0, 1, 0);

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

	if (currentBullet[BulletState] > 0)
	{

		if (time->testTime(index))	//Count time
		{
			currentBullet[BulletState] -= 1;	//Take away one bullet
			//DO BULLET STUFF HERE
			theArrayofEntities->push_back((theFactory->Create(BULLET)));
			theArrayofEntities->back()->SetPos(theHero->GetX(), theHero->GetY());
			thePointertoBullet = (dynamic_cast<bullet*> (theArrayofEntities->back()));
			thePointertoBullet->SetAngle(theHero->HeroRotation);
			thePointertoBullet->SetPower(power[BulletState]);
			--totalbullet[BulletState];
		}
		prevshot[BulletState] = currentshot[BulletState];

	}

	if (currentBullet[BulletState] <= 0)	//AUTO RELOAD
	{
		currentreload[BulletState] = timeGetTime();
		if (reloadC == false){
			prevreload[BulletState] = currentreload[BulletState];
			reloadC = true;
		}
		if (currentreload[BulletState] - prevreload[BulletState] >= reloadtime[BulletState])
		{
			ReloadGun();
			reloadC = false;
		}
	}

}

void gun::ReloadGun()
{
	if (bulletCount >= 0)	//CHECK IF YOU HAVE ENOUGH AMMO
	{

		if (currentBullet[BulletState] >= bulletCount[BulletState])		//IF LESS BULLET THAN RELOADABLE COUNT, USE ALL BULLETS LEFT
		{
			currentBullet[BulletState] += bulletCount[BulletState];
			bulletCount[BulletState] = 0;
		}
		else
		{
			bulletCount[BulletState] = bulletCount[BulletState] - (ReloadBullet[BulletState] - currentBullet[BulletState]);
			currentBullet[BulletState] = ReloadBullet[BulletState];//ELSE SET CURRENT BULLET TO 30 AND MINUS OFF BULLET COUNT

		}
	}
}

void gun::InitGun()
{
	StateNow = pistol;
		bulletCount[0] = 18;
		currentBullet[0] = 15;
		ReloadBullet[0] = 15;

		power[0] = 1000;
		firing = false;
		prevshot[0] = 0;
		currentshot[0] = 0;
		currentreload[0] = 0;
		prevreload[0] = 0;
		reloadtime[0] = 100;
		reloadC = false;

		MilliSecondPerShot[0] = 500;

		totalbullet[0] = bulletCount[0] + currentBullet[0];

		bulletCount[1] = 60;
		currentBullet[1] = 30;
		ReloadBullet[1] = 30;

		power[1] = 2000;
		firing = false;
		prevshot[1] = 0;
		currentshot[1] = 0;
		currentreload[1] = 0;
		prevreload[1] = 0;
		reloadtime[1] = 100;
		reloadC = false;

		MilliSecondPerShot[1] = 50;

		totalbullet[1] = bulletCount[1] + currentBullet[1];




		bulletCount[2] = 9;
		currentBullet[2] = 9;
		ReloadBullet[2] = 9;

		power[2] = 10000;
		firing = false;
		prevshot[2] = 0;
		currentshot[2] = 0;
		currentreload[2] = 0;
		prevreload[2] = 0;
		reloadtime[2] = 100;
		reloadC = false;

		MilliSecondPerShot[2] = 1100;

		totalbullet[2] = bulletCount[2] + currentBullet[2];

}

void gun::SetArray(vector<CEntity*> & theArrayofEntities)
{
	this->theArrayofEntities = &theArrayofEntities;
}

void gun::SetFactory(CEntityFactory & theFactory)
{
	this->theFactory = &theFactory;
}

void gun::changestate(GunStates theState)
{
	switch (theState)
	{
	case pistol:
		StateNow = pistol;
		BulletState = 0;
		break;
	case uzi:
		StateNow = uzi;
		BulletState = 1;
		break;
	case shotgun:
		StateNow = shotgun;
		BulletState = 2;
		break;
	}
	time->resetTime(index);//have a time reference
	time->changeLimit(index, MilliSecondPerShot[BulletState]);//reset time and change limit
}