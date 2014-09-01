#pragma once
#include "loadTGA.h"
#include "../gl/freeglut.h"

class UI
{
private:
	void *font_style;
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

	void RedHealth(void);

	void WhiteHealth(void);

	void RenderUI(StateType States);

	int DetermineState(int choice);

	void printw (float x, float y, float z, char* format, ...);

	loadTGA theTexture;
};

