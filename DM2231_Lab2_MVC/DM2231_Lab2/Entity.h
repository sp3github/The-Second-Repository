#pragma once
#include "Header.h"
#include <vector>
#include "vector3D.h"


enum Entity{
 HEALTH = 0,
 AMMO ,
 SLOWDOWN ,
 PLAYER ,
 BULLET,
 ZOMBIE,
 OBSTACLE,
 CASINO,
 BUILDING,
 SPZOMBIE
};


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

	virtual void update(float dt);

	virtual void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	virtual void update(int zombiecount);
	//virtual void update(int herox, int heroy, float dt);

	virtual void render(int mapOffset_x, int mapOffset_y);

	virtual void CollisionEvent(CEntity &other, vector<CEntity*> & theArray);
	bool Destroy;

	int hp;
	Vector3D<float> pos;
	Vector3D<float> vel;

	Entity ID;
	TextureImage tex;
};

