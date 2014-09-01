#pragma once
#include "vector3D.h"
#include "Header.h"
#include "Entity.h"
#include <time.h>
#include "MVCtime.h"

enum ZombieStates
{
	normal,
	fast,
	slow
};

class CZombies : public CEntity
{
protected:
	int CurrentState;
	const int ATTACK;
	const int IDLE;
	const int REPEL;
protected:
	bool ChangeState(const int newState);
private:
	
	unsigned int walk, attack, die;
	int health, moneysteal;
	bool iswalk, isattack, isdead;	

	void SetZombieState(int num);
	int GetZombieState();

	const int hero_x;
	const int hero_y;
public:
	CZombies(void);
	~CZombies(void);
	//Overloaded Constructor

	int CalculateDistance(int hero_x, int hero_y);

	bool bounce;
	Vector3D<float> BounceDir;
	void deceasingHealth(int num);
	int getHealth();
	int getZombieCount();
	int getMoneySteal();
	bool isDead();
	void setStats(int health, int moneysteal);
	


	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);

	//void update(int herox, int heroy, float dt);

	void drawzombie(int x, int y);
	vector<CEntity*>::iterator  CollisionEvent(CEntity &other, vector<CEntity*> & theArray);


	mvcTime * Timer;
	int TimeIndex;

	int zombie;

	void setZombie(ZombieStates zombieState);
};