#pragma once
#include "../irrKlang/irrKlang.h"

using namespace irrklang;

class Sound
{
public:
	/*
		Sound Type
	*/
	enum SoundType{
	MENU = 0,
	SHOP,
	LEVEL,
	PISTOL,
	SHOTGUN,
	UZI,
	RELOAD,	
	EXPLOSION,
	HEALTH,
	AMMO,
	SLOWDOWN,
	CREDIT,
	ZOMBIE,
	MOUSE
	};

	Sound(void);
	~Sound(void);

	/*
		Sound engine
	*/
	ISoundEngine* theSoundEngine;
	ISound* Menu;
	ISound* Shop;
	ISound* Level;
	ISound* Pistol;
	ISound* Shotgun;
	ISound* Uzi;
	ISound* Reload;
	ISound* Explosion;
	ISound* Health;
	ISound* Ammo;
	ISound* Slowdown;
	ISound* Credit;
	ISound* Zombie;
	ISound* Mouse;

	/*
		Function to initialise all the sound
	*/
	bool InitSound(void);

	/*
		Function to play the sound
	*/
	void RenderSound (SoundType Sounds);
};