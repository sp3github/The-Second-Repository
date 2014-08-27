#include "DM2231_Model.h"

DM2231_Model::DM2231_Model(void):theCollision(TestMap)
{
	//theUI = new UI;
}

DM2231_Model::~DM2231_Model(void)
{
	//if(theUI)
	//{
	//	delete theUI;
	//}
}

// Update the model
void DM2231_Model::Update(void)
{

	theHero->HeroRotation = AnglefromHerotoMouse();
	
	theHero->ConstrainHero(20, /*(TestMap.getNumOfTiles_ScreenWidth() * TILE_SIZE) - 20*/ 300, 20, (TestMap.getNumOfTiles_ScreenHeight() * TILE_SIZE) - 20, 1.0f, TestMap.mapOffset_x, TestMap.mapOffset_y);
	TestMap.Update();

	for(auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
	{
		CEntity * go = (*it);

		for(auto i = ArrayofEntities.begin(); i != ArrayofEntities.end(); i++)
		{
			CEntity * other = (*i);
			if(go != other)
				theCollision.CheckCollision(go,other,false,false,false,false);
		}
	}
}

float DM2231_Model::AnglefromHerotoMouse()
{
	Vector3D<float> MouseVector(theMouseInfo.MousePos);
	Vector3D<float> HeroVector(theHero->GetX(), theHero->GetY());

	float deltaY = MouseVector.y - HeroVector.y;
	float deltaX = MouseVector.x - HeroVector.x;

	return atan2(deltaY, deltaX) * 180 / PI;
}
