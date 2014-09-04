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
	ENTERNAME,
	STORYIN,
	STARTSCREEN,
	LEVEL,
	SUBSHOP,
	SHOP,
	CREDIT,
	WIN,
	DEFEAT,
	SUBPAGE,
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

