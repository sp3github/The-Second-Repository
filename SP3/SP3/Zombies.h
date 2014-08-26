//#pragma once
//#ifndef CZOMBIES_H
//#define CZOMBIES_H
//
//#include "Define.h"
//class CZombies
//{
//private:
//	std::vector<unsigned int> frames;
//	unsigned int walk, attack, die;
//	unsigned int curframe;
//
//	int health, strength;
//	float speed;
//	vector3D direction;
//	vector3D rotation;
//	bool iswalk, isattack, isdead;
//
//	//collision
//	//collisionsphere cs;
//public:
//	//CZombies(void);
//	~CZombies(void);
//	CZombies(std::vector<unsigned int> anim
//			, unsigned int w, unsigned int a, unsigned int d
//			, int h, int str, float spd/*, collisionsphere css*/);
//	bool Update(/*std::vector<collision plane>& col,*/ vector3D playerLoc);
//	void show(); //show zombie
//	bool setAttack(/*collisionpshere player*/);
//	/*collisionsphere* getCollisonSphere();*/
//	void setLocation(vector3D newloc);
//	void deceasingHealth(int num);
//	int getHealth();
//	int getStrength();
//	bool isDead();
//};
//#endif