#pragma once
#include "Header.h"

typedef int Entity;
#define HEALTH 0
#define AMMO 1
#define SLOWDOWN 2
#define PLAYER 3

class CEntity
{
private:
	int pos_x;
	int pos_y;
public:
	CEntity(void);
	~CEntity(void);

	int GetX(void);
	int GetY(void);

	void SetPos(const int pos_x, const int pos_y);
	void Set_Y(int pos_y);
	void Set_X(int pos_x);

	int movementspeed;
	int tile_size;

	virtual void update() = 0;
	virtual void render(int mapOffset_x, int mapOffset_y) = 0;

	virtual bool CollisionEvent(CEntity &other);
	
	Entity ID;
};

