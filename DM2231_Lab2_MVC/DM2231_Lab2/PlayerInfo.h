#pragma once
#include "Header.h"
#include <vector>
#include "Entity.h"

class CPlayerInfo : public CEntity
{
public:
	CPlayerInfo(void);
	~CPlayerInfo(void);

	float HeroRotation;

	TextureImage HeroTexture[3];

	// Render the Hero onto the screen
	void render(int mapOffset_x, int mapOffset_y);
	void update();
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
	void ConstrainHero( const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, const int LsoftBorder, const int RsoftBorder, const int TsoftBorder, const int BsoftBorder, float timeDiff, int& mapOffset_x, int& mapOffset_y, int mapheight, int mapwidth);

	int m_iTileSize;

	void moveMeUpDown(bool mode, float timeDiff, float movementspeed);
	void moveMeLeftRight(bool mode, float timeDiff, float movementspeed);

	bool CollisionEvent(CEntity &other, vector<CEntity*> & theArray);

	int hp;
	int ammo;
	bool slow;

private:

	bool heroAnimationInvert;
	int heroAnimationCounter;

	
};
