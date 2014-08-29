#pragma once
#include "vector3D.h"
#include "Header.h"
#include "Entity.h"
#include <time.h>

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
	Vector3D<float> vel;
	Vector3D<float> pos;
	bool iswalk, isattack, isdead;	

	void SetZombieState(int num);
	int GetZombieState();

	const int hero_x;
	const int hero_y;

	//int EnemyArray[];
public:
	CZombies(void);
	~CZombies(void);
	//Overloaded Constructor
   //CZombies( unsigned int w, unsigned int a, unsigned int d, int h, int st, float spd);

	int CalculateDistance(const int hero_x, const int hero_y);
	void Update();

	void deceasingHealth(int num);
	int getHealth();
	int getMoneySteal();
	bool isDead();
	
	void update(int herox, int heroy);
	void render();
	void drawzombie(int x, int y);
	int i;


};