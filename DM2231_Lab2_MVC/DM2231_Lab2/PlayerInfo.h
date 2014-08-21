#pragma once
#include "Header.h"


class CPlayerInfo
{
public:
	CPlayerInfo(void);
	~CPlayerInfo(void);

	TextureImage HeroTexture[3];

	// Render the Hero onto the screen
	void RenderHero(void);

	// Initialise this class instance
	void Init(void);


	// Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(int heroAnimationCounter);
	// Get Animation Counter of the player
	int GetAnimationCounter(void);

	// Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, 
					   const int topBorder, const int bottomBorder, 
					   float timeDiff,
					   int& mapOffset_x, int& mapOffset_y);

	int m_iTileSize;
	int movementspeed;

private:
	

	// Hero's information
	int hero_x, hero_y;

	bool heroAnimationInvert;
	int heroAnimationCounter;

	
};
