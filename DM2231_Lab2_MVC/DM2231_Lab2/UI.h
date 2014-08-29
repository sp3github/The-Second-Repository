#pragma once
#include "loadTGA.h"
#include "../gl/freeglut.h"

class UI
{
private:
	void *font_style;
public:
	enum StateType{
	PAUSE = 0,
	LEVEL,
	STARTSCREEN,
	SUBPAGE,
	ITEM,
	VICTORY,
	DEFEAT,
	WINLEVEL,
	SHOP
	};

	UI(void);
	~UI(void);

	void RenderUI(StateType States);

	int DetermineState(int choice);

	void printw (float x, float y, float z, char* format, ...);

	loadTGA theTexture;
};

