#include "Map.h"

CMap::CMap(void)
: theScreen_Height(0)
, theScreen_Width(0)
, theMap_Height(0)
, theMap_Width(0)
, theNumOfTiles_ScreenHeight(0)
, theNumOfTiles_ScreenWidth(0)
, theNumOfTiles_MapHeight(0)
, theNumOfTiles_MapWidth(0)
, theTileSize(0)
{
	mapOffset_x = 0, mapOffset_y = 0;
	tileOffset_x = 0, tileOffset_y = 0;
	mapFineOffset_x = 0, mapFineOffset_y = 0;
	theScreenMap.clear();
}

CMap::~CMap(void)
{
	theScreenMap.clear();
}

void CMap::Init(const int theScreen_Height, const int theScreen_Width, 
				const int theMap_Height, const int theMap_Width, 
				const int theTileSize)
{
	this->theScreen_Height = theScreen_Height;
	this->theScreen_Width = theScreen_Width;
	this->theMap_Height = theMap_Height;
	this->theMap_Width = theMap_Width;
	this->theTileSize = theTileSize;

	theNumOfTiles_ScreenHeight = (int) (theScreen_Height / theTileSize);
	theNumOfTiles_ScreenWidth = (int) (theScreen_Width / theTileSize);
	theNumOfTiles_MapHeight = (int) (theMap_Height / theTileSize);
	theNumOfTiles_MapWidth = (int) (theMap_Width / theTileSize);

	theScreenMap.resize(theNumOfTiles_MapHeight);
	for (int i = 0; i < theNumOfTiles_MapHeight; ++i)
		theScreenMap[i].resize(theNumOfTiles_MapWidth);
}

bool CMap::LoadMap(const string mapName)
{
	cout<<mapName<<endl;
	if (LoadFile(mapName) == true)
	{
		printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
		return true;
	}
	return false;
}

bool CMap::LoadFile(const string mapName)
{
	int theLineCounter = 0;
	int theMaxNumOfColumns = 0;

	ifstream file(mapName);
	if(file.is_open())
	{
		int i = 0, k = 0;
		while(file.good())
		{
			string aLineOfText = "";
			getline(file, aLineOfText);

			// If this line is not a comment line, then process it
			if(!(aLineOfText.find("//") == NULL) && aLineOfText != "")
			{
				if (theLineCounter == 0)
				{
					// This is the first line of the map data file
					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{
						// Count the number of columns
						theMaxNumOfColumns = atoi(token.c_str());
					}
				}
				else
				{
					int theColumnCounter = 0;

					string token;
					istringstream iss(aLineOfText);
					while(getline(iss, token, ','))
					{

						theScreenMap[theLineCounter - 1][theColumnCounter++] = atoi(token.c_str());
					}
				}
			}	
			theLineCounter++;
		}
	}
	else
	{
		return false;
	}
	return true;
}

// Get the number of tiles for height of the screen
int CMap::getNumOfTiles_ScreenHeight(void)
{
	return theNumOfTiles_ScreenHeight;
}

// Get the number of tiles for width of the screen
int CMap::getNumOfTiles_ScreenWidth(void)
{
	return theNumOfTiles_ScreenWidth;
}

// Get the number of tiles for height of the map
int CMap::getNumOfTiles_MapHeight(void)
{
	return theNumOfTiles_MapHeight;
}

// Get the number of tiles for width of the map
int CMap::getNumOfTiles_MapWidth(void)
{
	return theNumOfTiles_MapWidth;
}

void CMap::LoadLevel(int level)
{
	switch (level)
	{
	case 1:
		Init(600, 800, 1200, 1600, TILE_SIZE);
		LoadMap("Levels\\MapDesign2.csv");

		break;
	case 2:
		LoadMap("Levels\\MapDesign3.csv");
		break;
	default:
		break;
	}

}

void CMap::RenderTileMap(void)
{
	mapFineOffset_x = mapOffset_x % TILE_SIZE;
	mapFineOffset_y = mapOffset_y % TILE_SIZE;

	glPushMatrix();
	for(int i = 0; i < getNumOfTiles_ScreenHeight()+1; i ++)
	{
		for(int k = 0; k < getNumOfTiles_ScreenWidth()+1; k ++)
		{
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ( (tileOffset_x + k) >= getNumOfTiles_MapWidth() )
				break;
			if( (tileOffset_y + i) >= getNumOfTiles_MapHeight())
				break;
			if( (tileOffset_y + i) <= 0)
				break;
			glPushMatrix();
			glTranslatef(k*TILE_SIZE-mapFineOffset_x, i*TILE_SIZE - mapFineOffset_y, 0);
			glEnable( GL_TEXTURE_2D );
			glEnable( GL_BLEND );
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if (theScreenMap[tileOffset_y + i][tileOffset_x + k] == 1)
				glColor3f(0,0,0);

			glBegin(GL_QUADS);
				glTexCoord2f(0,1); glVertex2f(0,0);
				glTexCoord2f(0,0); glVertex2f(0,TILE_SIZE);
				glTexCoord2f(1,0); glVertex2f(TILE_SIZE,TILE_SIZE);
				glTexCoord2f(1,1); glVertex2f(TILE_SIZE,0);
			glEnd();
			glDisable( GL_BLEND );
			glDisable( GL_TEXTURE_2D );
			glPopMatrix();
		}
	}
	glPopMatrix();

}

void CMap::Update()
{
	tileOffset_x = (int) (mapOffset_x / TILE_SIZE);
	if (tileOffset_x+getNumOfTiles_ScreenWidth() > getNumOfTiles_MapWidth())
		tileOffset_x = getNumOfTiles_MapWidth() - getNumOfTiles_ScreenWidth();

	tileOffset_y = (int) (mapOffset_y / TILE_SIZE);
	if (tileOffset_y+getNumOfTiles_ScreenHeight() > getNumOfTiles_MapHeight())
		tileOffset_y = getNumOfTiles_MapHeight() - getNumOfTiles_ScreenHeight();
}

bool CMap::LoadItems(vector<CEntity*> &theArray, CEntityFactory &theFac)
{
	for (int i = 0; i <getNumOfTiles_MapHeight(); ++i)
	{
		for (int j = 0; j < getNumOfTiles_MapWidth(); ++j)
		{
			switch (theScreenMap[i][j])
			{
			case 2:
				{
					bool Found = false;
					CEntity * hero = NULL;
					for(auto it = theArray.begin(); it != theArray.end(); it++)
					{
						if((*it)->ID == PLAYER)
						{
							Found = true;
							hero = (*it);
							break;
						}
					}
					if(!Found)
					{
						theArray.push_back(theFac.Create(PLAYER));
						hero = theArray.back();
					}
					hero->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				}
				break;
			case 3:
				theArray.push_back(theFac.Create(HEALTH));
				theArray.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				break;
			case 4:
				theArray.push_back(theFac.Create(AMMO));
				theArray.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				break;
			case 5:
				theArray.push_back(theFac.Create(SLOWDOWN));
				theArray.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				break;
			case 6:
				theArray.push_back(theFac.Create(ZOMBIE));
				theArray.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				break;
			case 10:
			case 11:
			case 12:
			case 13:
				theArray.push_back(theFac.Create(BUILDING));
				theArray.back()->SetPos(j * TILE_SIZE, i * TILE_SIZE);
				break;
			default:
				break;
			}


		}
	}
	return true;
}