#pragma once
#include "loadTGA.h"
#include "gun.h"
#include "Sound.h"

class UI
{
private:
	float PlayerHP;
public:
	enum StateType{
	LEVEL = 0,
	STARTSCREEN,
	SUBPAGE,
	CREDIT,
	WIN,
	DEFEAT,
	SHOP
	};

	UI(void);
	~UI(void);

	void SetHP(float currentHP, float maxHP);

	float GetHP(void);

	void RenderUI(StateType States,const GLuint &base);

	void printw (float x, float y, float z,const GLuint &base, const char* format, ...);

	void SetGun(gun & theGun);

	loadTGA theTexture;

	gun * theGun;

	Sound theSound;
};

