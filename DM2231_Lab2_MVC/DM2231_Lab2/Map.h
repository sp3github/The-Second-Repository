#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Entity.h"
#include "EntityFactory.h"
#include "Header.h"

class CMap
{
public:
	CMap(void);
	~CMap(void);

	void Init( int theScreen_Height, int theScreen_Width, 
		       const int theMap_Height, const int theMap_Width, 
		       const int theTileSize);
	bool LoadMap(const string mapName);

	int getNumOfTiles_ScreenHeight(void);	// Get the number of tiles for height of the screen
	int getNumOfTiles_ScreenWidth(void);	// Get the number of tiles for width of the screen
	int getNumOfTiles_MapHeight(void);		// Get the number of tiles for height of the map
	int getNumOfTiles_MapWidth(void);		// Get the number of tiles for width of the map

	vector<vector<int> > theScreenMap;

	void LoadLevel(int level);

	void RenderTileMap();

	TextureImage TileMapTexture[1];
	int mapOffset_x, mapOffset_y;
	int tileOffset_x, tileOffset_y;
	int mapFineOffset_x, mapFineOffset_y;

	void Update();

	void LoadItem(vector<CEntity*> & theArray,CEntityFactory & theFac);

private:
	int theScreen_Height;
	int theScreen_Width;
	int theMap_Height;
	int theMap_Width;
	int theNumOfTiles_ScreenHeight;
	int theNumOfTiles_ScreenWidth;
	int theNumOfTiles_MapHeight;
	int theNumOfTiles_MapWidth;
	int theTileSize;

	bool LoadFile(const string mapName);
};
