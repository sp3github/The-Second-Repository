#include "Sound.h"
#include <iostream>

using namespace std;

Sound::Sound(void)
: theSoundEngine(NULL)
, Menu(NULL)
, Shop(NULL)
, Level(NULL)
, Pistol(NULL)
, Shotgun(NULL)
, Uzi(NULL)
, Reload(NULL)
, Explosion(NULL)
, Health(NULL)
, Ammo(NULL)
, Slowdown(NULL)
, Credit(NULL)
, Zombie(NULL)
, Mouse(NULL)
{
}


Sound::~Sound(void)
{
}

bool Sound::InitSound(void)
{
	// Start the sound engine
	theSoundEngine = createIrrKlangDevice();
		if (!theSoundEngine)
			return false;		// Error starting up the sound engine
}

void Sound::RenderSound(SoundType Sounds)
{
	switch(Sounds)
	{
		case MENU:
		// Plays menu page sound
		if(Menu == NULL)
		{
			Menu = theSoundEngine->play2D(("Sound/Menu.wav"), true, true);
		}
		if (Menu->getIsPaused() == true)
		{
			Menu->setIsPaused(false);
		}
		else if (Menu->isFinished() == true)
		{
			Menu = NULL;
		}
		break;

		case SHOP:
		// Plays sub page sound
		if(Shop == NULL)
		{
			Shop = theSoundEngine->play2D(("Sound/Subpage.wav"), false, true);
		}
		if (Shop->getIsPaused() == true)
		{
			Shop->setIsPaused(false);
		}
		else if (Shop->isFinished() == true)
		{
			Shop = NULL;
		}
		break;

		case LEVEL:
		// Plays level sound
		if(Level == NULL)
		{
			Level = theSoundEngine->play2D(("Sound/Level.wav"), false, true);
		}
		if (Level->getIsPaused() == true)
		{
			Level->setIsPaused(false);
		}
		else if (Level->isFinished() == true)
		{
			Level = NULL;
		}
		break;

		case PISTOL:
		// Plays the pistol sound
		if(Pistol == NULL)
		{
			Pistol = theSoundEngine->play2D(("Sound/Pistol.wav"), false, true);
		}
		if (Pistol->getIsPaused() == true)
		{
			Pistol->setIsPaused(false);
		}
		else if (Pistol->isFinished() == true)
		{
			Pistol = NULL;
		}
		break;

		case SHOTGUN:
		// Plays the shotgun sound
		if(Shotgun == NULL)
		{
			Shotgun = theSoundEngine->play2D(("Sound/Shotgun.wav"), false, true);
		}
		if (Shotgun->getIsPaused() == true)
		{
			Shotgun->setIsPaused(false);
		}
		else if (Shotgun->isFinished() == true)
		{
			Shotgun = NULL;
		}
		break;

		case UZI:
		// Plays the uzi sound
		if(Uzi == NULL)
		{
			Uzi = theSoundEngine->play2D(("Sound/Uzi.wav"), false, true);
		}
		if (Uzi->getIsPaused() == true)
		{
			Uzi->setIsPaused(false);
		}
		else if (Uzi->isFinished() == true)
		{
			Uzi = NULL;
		}
		break;

		case RELOAD:
		// Plays the reload sound
		if(Reload == NULL)
		{
			Reload = theSoundEngine->play2D(("Sound/Reload.wav"), false, true);
		}
		if (Reload->getIsPaused() == true)
		{
			Reload->setIsPaused(false);
		}
		else if (Reload->isFinished() == true)
		{
			Reload = NULL;
		}
		break;

		case EXPLOSION:
		// Plays the explosion sound
		if(Explosion == NULL)
		{
			Explosion = theSoundEngine->play2D(("Sound/Explosion.wav"), false, true);
		}
		if (Explosion->getIsPaused() == true)
		{
			Explosion->setIsPaused(false);
		}
		else if (Explosion->isFinished() == true)
		{
			Explosion = NULL;
		}
		break;

		case HEALTH:
		// Plays the health sound
		if(Health == NULL)
		{
			Health = theSoundEngine->play2D(("Sound/Health.wav"), false, true);
		}
		if (Health->getIsPaused() == true)
		{
			Health->setIsPaused(false);
		}
		else if (Health->isFinished() == true)
		{
			Health = NULL;
		}
		break;

		case AMMO:
		// Plays the ammo sound
		if(Ammo == NULL)
		{
			Ammo = theSoundEngine->play2D(("Sound/Ammo.wav"), false, true);
		}
		if (Ammo->getIsPaused() == true)
		{
			Ammo->setIsPaused(false);
		}
		else if (Ammo->isFinished() == true)
		{
			Ammo = NULL;
		}
		break;

		case SLOWDOWN:
		// Plays the zombie slowdown sound
		if(Slowdown == NULL)
		{
			Slowdown = theSoundEngine->play2D(("Sound/Slowdown.wav"), false, true);
		}
		if (Slowdown->getIsPaused() == true)
		{
			Slowdown->setIsPaused(false);
		}
		else if (Slowdown->isFinished() == true)
		{
			Slowdown = NULL;
		}
		break;

		case CREDIT:
		// Plays the score page sound
		if(Credit == NULL)
		{
			Credit = theSoundEngine->play2D(("Sound/Score.wav"), false, true);
		}
		if (Credit->getIsPaused() == true)
		{
			Credit->setIsPaused(false);
		}
		else if (Credit->isFinished() == true)
		{
			Credit = NULL;
		}
		break;

		case ZOMBIE:
		// Plays the zombie changing to human sound
		if(Zombie == NULL)
		{
			Zombie = theSoundEngine->play2D(("Sound/Zombie.wav"), false, true);
		}
		if (Zombie->getIsPaused() == true)
		{
			Zombie->setIsPaused(false);
		}
		else if (Zombie->isFinished() == true)
		{
			Zombie = NULL;
		}
		break;

		case MOUSE:
		// Plays mouse clicking sound
		if(Mouse == NULL)
		{
			Mouse = theSoundEngine->play2D(("Sound/Mouse.wav"), false, true);
		}
		if  (Mouse->getIsPaused() == true)
		{
			Mouse->setIsPaused(false);
		}
		else if (Mouse->isFinished() == true)
		{
			Mouse = NULL;
		}
		break;
	}
}
