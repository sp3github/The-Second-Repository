#pragma once
#include "../irrKlang/irrKlang.h"
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
using namespace irrklang;

class Sound
{
public:
	/*
		Sound Type
	*/
	enum SoundType{
	MENU = 0,
	SUBPAGE,
	LEVEL,
	PISTOL,
	SHOTGUN,
	UZI,
	RELOAD,	
	EXPLOSION,
	HEALTH,
	AMMO,
	SLOWDOWN,
	SCORE,
	ZOMBIE,
	};

	Sound(void);
	~Sound(void);

	/*
		Sound engine
	*/
	ISoundEngine* theSoundEngine;
	ISound* Menu;
	ISound* Subpage;
	ISound* Level;
	ISound* Pistol;
	ISound* Shotgun;
	ISound* Uzi;
	ISound* Reload;
	ISound* Explosion;
	ISound* Health;
	ISound* Ammo;
	ISound* Slowdown;
	ISound* Score;
	ISound* Zombie;

	/*
		Function to initialise all the sound
	*/
	bool InitSound(void);

	/*
		Function to play the sound
	*/
	void RenderSound (SoundType Sounds);
};