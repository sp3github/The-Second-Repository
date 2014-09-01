#include "DM2231_Model.h"

#define LEFT_BORDER TILE_SIZE*1
#define BOTTOM_BORDER TILE_SIZE*1

DM2231_Model::DM2231_Model(void) :theCollision(TestMap,ArrayofEntities)
{
	time = mvcTime::getInstance();
	//theUI = new UI;
	IndexTime[0] = time->insertNewTime(3000);
	SetTimeDefeat = false;
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

		//UPDATE THE MAP
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

		//CHECK FOR COLLISION
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
					cout << go->ID << endl;
					if (!theCollision.CheckCollision(go, other, false, false, false, false)) //Checks if it has collided go with other
					{
						i = go->CollisionEvent(*other, ArrayofEntities);        //Run collision code, setting i to the iterator which is returned.
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


		}

		//if (//if zombie count = 0 )
		{
			//theState.theState = theState.win;
		}
		if (theHero->hp <= 0)
		{
			theState.theState = theState.defeat;
		}

	}
	else if(theState.theState == theState.defeat)
	{
		//if(!SetTimeDefeat)
		//{
		//	time->resetTime(IndexTime[0]);
		//	SetTimeDefeat = true;
		//}
		//else if(time->testTime(IndexTime[0]))
		//{
		//	theState.theState = theState.credit;

		//	SetTimeDefeat = false;
		//	ArrayofEntities.clear();
		//	SetStart();
		//}


	}

	if(theState.theState == theState.credit)
	{
		time->resetTime(IndexTime[0]);
	}
	theUI.SetHP(theHero->hp,100);
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

void DM2231_Model::SetStart()
{
	TestMap.LoadLevel(1);
	TestMap.LoadItems(ArrayofEntities,theEntityFactory);

	for (auto it = ArrayofEntities.begin(); it != ArrayofEntities.end(); it++)
	{
		if ((*it)->ID == PLAYER)
		{
			theHeroEntity = (*it);
			theHero = (dynamic_cast<CPlayerInfo*>(*it));
			break;
		}
	}

	thegun.SetPlayer(*theHero);
	thegun.SetArray(ArrayofEntities);
	thegun.SetFactory(theEntityFactory);
	

	for (int zombie = 0; zombie < 2; zombie++)
	{
		ArrayofEntities.push_back(theEntityFactory.Create(ZOMBIE));
	}
}