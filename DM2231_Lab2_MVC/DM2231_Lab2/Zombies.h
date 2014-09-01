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

	int i;
<<<<<<< HEAD
	bool bounce;
	Vector3D<float> BounceDir;

=======
>>>>>>> origin/weijie
public:
	CZombies(void);
	~CZombies(void);
	//Overloaded Constructor
    //CZombies( unsigned int w, unsigned int a, unsigned int d, int h, int st, float spd);

	int CalculateDistance(int hero_x, int hero_y);
	void update();

	void deceasingHealth(int num);
	int getHealth();
	int getZombieCount();
	int getMoneySteal();
	bool isDead();
	void setStats(int health, int moneysteal);
	
<<<<<<< HEAD
	void update(int herox, int heroy, int mapOffset_x, int mapOffset_y, float dt);
	void render(int mapOffset_x, int mapOffset_y);
=======
	void update(int herox, int heroy, float dt);
	void renderN(int mapOffset_x, int mapOffset_y);
	void renderF(int mapOffset_x, int mapOffset_y);
	void renderS(int mapOffset_x, int mapOffset_y);
>>>>>>> origin/weijie
	void drawzombie(int x, int y);
	vector<CEntity*>::iterator  CollisionEvent(CEntity &other, vector<CEntity*> & theArray);

<<<<<<< HEAD
	mvcTime * Timer;
	int TimeIndex;
=======
	int zombie;
>>>>>>> origin/weijie

	void setZombie(ZombieStates zombieState);
};