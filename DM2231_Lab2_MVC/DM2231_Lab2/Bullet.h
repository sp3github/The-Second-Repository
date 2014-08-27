#pragma once
#include "Entity.h"

class Bullet : public CEntity
{
private:
	bool canFire;
	float x;
	float y;
	float velX;
	float velY;


public:
	Bullet(void);
	~Bullet(void);

	void FireBullet(float x, float y);
	void Tick();

	void render();
	void update();
};

