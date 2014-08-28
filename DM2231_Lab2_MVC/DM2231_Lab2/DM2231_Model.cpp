#include "DM2231_Model.h"

#define LEFT_BORDER TILE_SIZE*1
#define BOTTOM_BORDER TILE_SIZE*1

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
	ConstrainHero();	
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
		if(go->ID == Entity::ZOMBIE)
		{
			go->update(theHero->GetX(), theHero->GetY());
		}
		if (go->ID == Entity::OBSTACLE)
		{
			go->update(theObstacle.GetX(), theObstacle.GetY());
		}
		else 
		{
			go->update();
		}
		
		//if(go->ID == Entity::ZOMBIES)
		//{
		//	go->update(theHero->GetX(), therHero->GetY());
		//}	
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