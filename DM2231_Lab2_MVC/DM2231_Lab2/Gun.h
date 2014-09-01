#pragma once
#include "PlayerInfo.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "bullet.h"
#include <vector>
#include "MVCtime.h"

enum GunStates
{
	pistol,
	uzi,
	shotgun
};

class gun
{
public:
	gun();
	~gun();

	vector<CEntity*> *theArrayofEntities;
	CEntityFactory *theFactory;
	CPlayerInfo * theHero;
	bullet * thePointertoBullet;

	mvcTime * time;

	int index; 

	int tile_size;

	bool reloadC;
	bool firing;

	short int StateNow;

	short int totalbullet;
	short int bulletCount;
	short int currentBullet;
	short int ReloadBullet;
	short int power;
	short int MilliSecondPerShot;

	float prevshot;
	float currentshot;
	float reloadtime;
	float currentreload;
	float prevreload;
	float startReloadTime;

	float GunRenderOffset_x;
	float GunRenderOffset_y;

	void render();

	bool SetPlayer(CPlayerInfo &theHero);
	void FireGun();
	void ReloadGun();
	void SetArray(vector<CEntity *> & theArrayofEntities);
	void SetFactory(CEntityFactory & theFactory);

	void SetGun(GunStates theState);

};

