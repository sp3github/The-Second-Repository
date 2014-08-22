#pragma once
#include "DM2231_Controller.h"

class UI
{
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
	BET
	};

	UI(void);
	~UI(void);

	void RenderUI(StateType States);

	int DetermineState(int choice);

	void Click(void);

	loadTGA* theTexture;
};

