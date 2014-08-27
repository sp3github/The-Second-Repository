#pragma once
#include "Header.h"

<<<<<<< HEAD
enum Entity{
 HEALTH = 0,
 AMMO ,
 SLOWDOWN ,
 PLAYER ,
};


=======
enum Entity
{
HEALTH = 0,
AMMO ,
SLOWDOWN ,
PLAYER ,
};

>>>>>>> origin/THE-NEW-MASTER-BITCHES-PLZ-NO-DESTROY-AGAIN
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

	virtual void update();
	virtual void render(int mapOffset_x, int mapOffset_y);

	virtual bool CollisionEvent(CEntity &other);
	
	Entity ID;
};

