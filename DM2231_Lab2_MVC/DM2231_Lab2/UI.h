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

	void RenderUI(StateType States,const GLuint &base);


	void printw (float x, float y, float z,const GLuint &base, const char* format, ...);

	loadTGA theTexture;
};

