#pragma once
#include "Entity.h"
#include <vector>

class Bullet : public CEntity
{
private:
	bool canFire;
	float x;
	float y;
	float velX;
	float velY;
	float sx;
	float sy;

	std::vector<Bullet *> bulls;

public:
	Bullet(void);
	~Bullet(void);

	void FireBullet(float x, float y);
	void Tick();
	void Draw();
};
