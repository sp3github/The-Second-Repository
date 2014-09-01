#include "DM2231_Model.h"

#define LEFT_BORDER TILE_SIZE*1
#define BOTTOM_BORDER TILE_SIZE*1

DM2231_Model::DM2231_Model(void) :theCollision(TestMap,ArrayofEntities)
{
	time = mvcTime::getInstance();
	zombie = 5;
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

	if (theState.theState == State::level)
	{

		theHero->HeroRotation = AnglefromHerotoMouse();
		ConstrainHero();
		TestMap.Update();

		for (auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
		{
			CEntity * go = (*it);
			if (go->ID == BULLET)//Checl bullet against environment
			{
				if (!theCollision.CheckCollision(go, NULL, false, false, false, false, true))
				{
					ArrayofEntities.erase(it);
					go->~CEntity();
					break;
				}
			}

			if (go->ID == ZOMBIE)
			{
				go->update(theHero->GetX(), theHero->GetY(), TestMap.mapOffset_x, TestMap.mapOffset_y, time->getDelta());
			}

			go->update(time->getDelta());
		}

		for (auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
		{
			CEntity * go = NULL;
			go = (*it) ;
			//theHero->update();
			for (auto i = ArrayofEntities.begin(); i != ArrayofEntities.end();)
			{
				//Collision for entities. Collision Event returns the iterator after an element is erased.
				CEntity * other = (*i);
				if (go != other)
				{
					//cout << go->ID << endl;
					if (!theCollision.CheckCollision(go, other, false, false, false, false)) //Checks if it has collided go with other
					{
						i = go->CollisionEvent(*other, ArrayofEntities);	//Run collision code, setting i to the iterator which is returned.
						return;
						//break;
					}
					else
					{
						i++;
					}
				}
				else
				{
					i++;
				}
			}

			if (go->ID == OBSTACLE)
			{
				//theObstacle = (dynamic_cast<CObstacle*>(*it));
				//UpdateLimit();
				
			}
		
			go->update(time->getDelta());
		}

		////if (//if zombie count = 0 )
		//{
		//	theState.theState = theState.win;
		//}
		////else if (theHero->hp <= 0)
		//{
		//	theState.theState = theState.defeat;
		//	// When life count = 0, go to 'Defeat' page -> Credit
		//	//theHero->hp = 0;
		//}
		updateZombieCount();
		UpdateLimit();
	}
}

void DM2231_Model::UpdateLimit()
{
	if (zombiecount  <= 3)
	{
		zombiecount = 3;
	}

	if (zombiecount >= 11)
	{
		zombiecount = 11;
	}
}

int DM2231_Model::getZombieCount()
{
	return zombiecount;
}

void DM2231_Model::setZombieCount(int z)
{
	zombiecount = z;
}

void DM2231_Model::updateZombieCount()
{
	auto it = ArrayofEntities.begin();
	int Counter = 0;
	for( it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
	{
		if((*it)->ID == ZOMBIE)
		{
			Counter++;
		}
	}
	zombiecount = Counter;
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

