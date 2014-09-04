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
	short int BulletState;
	short int totalbullet[3];
	short int bulletCount[3];
	short int currentBullet[3];
	short int ReloadBullet[3];
	short int power[3];
	short int MilliSecondPerShot[3];

	float prevshot[3];
	float currentshot[3];
	float reloadtime[3];
	float currentreload[3];
	float prevreload[3];
	float startReloadTime[3];

	float GunRenderOffset_x;
	float GunRenderOffset_y;

	void render();

	bool SetPlayer(CPlayerInfo &theHero);
	void FireGun();
	void ReloadGun();
	void SetArray(vector<CEntity *> & theArrayofEntities);
	void SetFactory(CEntityFactory & theFactory);

	void InitGun();
	void changestate(GunStates theState);

};

