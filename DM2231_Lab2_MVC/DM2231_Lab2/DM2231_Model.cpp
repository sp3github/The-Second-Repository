#include "DM2231_Model.h"

#define LEFT_BORDER TILE_SIZE*1
#define BOTTOM_BORDER TILE_SIZE*1

DM2231_Model::DM2231_Model(void) :theCollision(TestMap,ArrayofEntities)
{
	time = mvcTime::getInstance();
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
	ConstrainHero();	
	TestMap.Update();

	for(auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
	{
		CEntity * go = (*it);

		for(auto i = ArrayofEntities.begin(); i != ArrayofEntities.end(); i++)
		{
			CEntity * other = (*i);
			if(go != other)
				if(theCollision.CheckCollision(go,other,false,false,false,false))
					break;
		}
		if(go->ID == BULLET)
		{
			if(!theCollision.CheckCollision(go,NULL,false,false,false,false,true))
			{
				ArrayofEntities.erase(it);
				go->~CEntity();
				break;
			}
		}
		go->update(time->getDelta());
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

void DM2231_Model::ConstrainHero()
{
	theHero->ConstrainHero(LEFT_BORDER, TestMap.getNumOfTiles_ScreenWidth() * TILE_SIZE,
		25, TestMap.getNumOfTiles_ScreenHeight() *TILE_SIZE,300,500,200,400,
		1.0f, TestMap.mapOffset_x, TestMap.mapOffset_y, TestMap.getNumOfTiles_ScreenHeight() * TILE_SIZE, TestMap.getNumOfTiles_ScreenWidth() * TILE_SIZE);
}