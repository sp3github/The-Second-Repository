#include "DM2231_Model.h"

#define LEFT_BORDER TILE_SIZE*1
#define BOTTOM_BORDER TILE_SIZE*1

DM2231_Model::DM2231_Model(void) :theCollision(TestMap, ArrayofEntities)
{
	time = mvcTime::getInstance();

	level = 1;


	IndexTime = time->insertNewTime(3000);
	SetTimeDefeat = false;
	SetTimeCredit = false;
	SetTimeWin = false;
	SetTimePageToLearnShop = false;
	SetTimeStoryIn = false;

	theMonWidth = static_cast<float>(GetSystemMetrics(SM_CXFULLSCREEN)) - 0.01 * static_cast<float>(GetSystemMetrics(SM_CXFULLSCREEN));
	theMonHeight = static_cast<float>(GetSystemMetrics(SM_CYFULLSCREEN)) - 0.01 * static_cast<float>(GetSystemMetrics(SM_CYFULLSCREEN));

	Wratio = theMonWidth / 800.f;
	Hratio = theMonHeight / 600.f;

	quad = new QuadTree(0, rect(0, 0, theMonWidth, theMonHeight));

	spZTrigger = true;
}

DM2231_Model::~DM2231_Model(void)
{
	//delete quad;
}

// Update the model
void DM2231_Model::Update(void)
{
	theUI.SetGun(thegun);

	switch (theState.theState)
	{
	case State::storyins:
		{
			if (!SetTimeStoryIn)
			{
				time->resetTime(IndexTime);
				SetTimeStoryIn = true;

			}
			else if (time->testTime(IndexTime))
			{
				TestMap.mapOffset_x = 0;
				TestMap.mapOffset_y = 0;
				theState.theState = theState.level;
				SetTimeStoryIn = false;
			}
		}
		break;

	case State::level:
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
						go->Destroy = true;
					}
				}

				if (go->ID == ZOMBIE)
				{
					go->update(theHero->GetX(), theHero->GetY(), TestMap.mapOffset_x, TestMap.mapOffset_y, time->getDelta());
				}

				if (go->ID == SPZOMBIE)
				{
					go->update(theHero->GetX(), theHero->GetY(), TestMap.mapOffset_x, TestMap.mapOffset_y, time->getDelta());
				}

				go->update(time->getDelta());
			}

			theUI.SetHP((float)theHero->hp, 100.0f);

			Collision();

			if (getZombieCount() == 0)
			{
				DeleteVectorButHero();
				if (level == 3)
				{
					theState.theState = theState.win;
				}
				else
				{
					level += 1;
					SetStart(level);
					theState.theState = theState.PageToLearnShop;
					TestMap.mapOffset_x = 0;
					TestMap.mapOffset_y = 0;
				}	
			}

		


			
				

			if (level == spZombie.level && spZTrigger == true)
			{
				for (int i = 0; i <TestMap.getNumOfTiles_MapHeight(); ++i)
				{
					for (int j = 0; j < TestMap.getNumOfTiles_MapWidth(); ++j)
					{
						switch (TestMap.theScreenMap[i][j])
						{

						case 11:
							ArrayofEntities.push_back(theEntityFactory.Create(SPZOMBIE));
							spZTrigger = false;
							ArrayofEntities.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
							break;
						}
					}
				}
				spZomb = (dynamic_cast<SPZombie*>(ArrayofEntities.back()));
				spZomb->setPlayerName(spZombie.zombiename);
				spZomb->GetBase(spZombie.base);
			}

			if (theHero->hp == 0 )
			{
				
				theState.theState = theState.defeat;

					spZombie.setPlayerName(theHero->playername);
					spZombie.getLevel(level);
					cout << "PLAYER DIED~!!!!!!!!!!!!" << endl;
					theHero->Init();
					DeleteVectorButHero();
					theHero->playername.clear();
					spZTrigger = true;
			}
		}
		break;
	case State::defeat:
		{
			if (!SetTimeDefeat)
			{
				time->resetTime(IndexTime);
				SetTimeDefeat = true;

			}
			else if (time->testTime(IndexTime))
			{
				TestMap.mapOffset_x = 0;
				TestMap.mapOffset_y = 0;
				theState.theState = theState.EnterName;
				SetTimeDefeat = false;
			}
			
		}
		break;
	case State::win:
		{
			if (!SetTimeWin)
			{
				time->resetTime(IndexTime);
				SetTimeWin = true;
			}
			else if (time->testTime(IndexTime))
			{
				theState.theState = theState.PageToLearnShop;
				SetTimeWin = false;
			}
			
		}
		break;
	case State::credit:
		{
			if (!SetTimeCredit)
			{
				time->resetTime(IndexTime);
				SetTimeCredit = true;
			}
			else if (time->testTime(IndexTime))
			{
				theState.theState = theState.menu;
				SetTimeCredit = false;
			}
			
		}
		break;
	case State::PageToLearnShop:
		{
			if (!SetTimePageToLearnShop)
			{
				time->resetTime(IndexTime);
				SetTimePageToLearnShop = true;
			}
			else if (time->testTime(IndexTime))
			{
				theState.theState = theState.shop;
				SetTimePageToLearnShop = false;
			}
		}
		break;
	case State::EnterName:
		{
			
			//if(theHero->playername.size() != 0)
			//{
			//	theHero->playername.clear();
			//	//theView->SetBackspace(false);
			//}

			DeleteVectorButHero();
			level = 1;
			SetStart(level);
		}
		break;
	default:
		break;
	}
}

int DM2231_Model::getZombieCount()
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
	return Counter;
}

void DM2231_Model::setZombieCount(int z)
{	
	zombiecount = z;
}

void DM2231_Model::UpdateLimit()
{
}

float DM2231_Model::AnglefromHerotoMouse()
{

	//Mouse vector is in screen pixel, while hero vector is in GL screen position.
	//Must use ratio to find the proper angle

	Vector3D<float> MouseVector(theMouseInfo.MousePos);


	Vector3D<float> HeroVector(theHero->GetX() * Wratio, theHero->GetY() * Hratio);

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

void DM2231_Model::SetStart(int level)
{
	TestMap.LoadLevel(level);
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
}


void DM2231_Model::DeleteVectorButHero()
{
	for(auto it = ArrayofEntities.begin(); it != ArrayofEntities.end();)
	{
		if((*it)->ID != PLAYER)
		{
			delete (*it);
			it = ArrayofEntities.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void DM2231_Model::Collision()
{
	quad->clear();
	for (int i = 0; i < ArrayofEntities.size(); i++)
	{
		if (ArrayofEntities[i]->ID == PLAYER)
			quad->insert(rect(ArrayofEntities[i]->GetX(), ArrayofEntities[i]->GetY(), ArrayofEntities[i]->tile_size, ArrayofEntities[i]->tile_size,ArrayofEntities[i]));
		else
			quad->insert(rect(ArrayofEntities[i]->GetX() - TestMap.mapOffset_x, ArrayofEntities[i]->GetY() - TestMap.mapOffset_y, ArrayofEntities[i]->tile_size, ArrayofEntities[i]->tile_size, ArrayofEntities[i]));
	}
	//ONLY INSERT OBJECTS THAT MOVE

	vector <rect> returnObjects;
	//temp vec to hold the returned guys.

	for (int i = 0; i < ArrayofEntities.size(); i++)
	{
		returnObjects.clear();
		if(ArrayofEntities[i]->movementspeed!=0)
		returnObjects = quad->retrive(returnObjects, (rect(ArrayofEntities[i]->GetX(), ArrayofEntities[i]->GetY(), ArrayofEntities[i]->tile_size, ArrayofEntities[i]->tile_size, ArrayofEntities[i])));

		for (int FirstCounter = 0; FirstCounter < returnObjects.size(); FirstCounter++)
		{
			for (int SecondCounter = 0; SecondCounter < returnObjects.size(); SecondCounter++)
			{
				if (returnObjects[FirstCounter].theEntity != returnObjects[SecondCounter].theEntity)
				{
					if (!theCollision.CheckCollision(returnObjects[FirstCounter].theEntity, returnObjects[SecondCounter].theEntity))
					{
						(returnObjects[FirstCounter].theEntity)->CollisionEvent(*returnObjects[SecondCounter].theEntity, ArrayofEntities);
					}
				}
			}
		}
	}

	//If collision sets something to be destroyed, destroy it here.
	for (auto it = ArrayofEntities.begin(); it != ArrayofEntities.end();)
	{
		CEntity * go = NULL;
		go = (*it);
		if (go->Destroy)
		{
			delete (*it);
			it = ArrayofEntities.erase(it);
			//it++;
		}
		else
		{
			it++;
		}
	}
}