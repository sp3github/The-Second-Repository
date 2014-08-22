#include "DM2231_Model.h"

DM2231_Model::DM2231_Model(void)
{

}

DM2231_Model::~DM2231_Model(void)
{
}

// Update the model
void DM2231_Model::Update(void)
{

	theHero->HeroRotation = AnglefromHerotoMouse();
	
	theHero->ConstrainHero(20, /*(TestMap.getNumOfTiles_ScreenWidth() * TILE_SIZE) - 20*/ 300, 20, (TestMap.getNumOfTiles_ScreenHeight() * TILE_SIZE) - 20, 1.0f, TestMap.mapOffset_x, TestMap.mapOffset_y);
	TestMap.Update();
}

float DM2231_Model::AnglefromHerotoMouse()
{
	Vector3D<float> MouseVector(theMouseInfo.MousePos);
	Vector3D<float> HeroVector(theHero->GetX(), theHero->GetY());

	float deltaY = MouseVector.y - HeroVector.y;
	float deltaX = MouseVector.x - HeroVector.x;

	return atan2(deltaY, deltaX) * 180 / PI;
}