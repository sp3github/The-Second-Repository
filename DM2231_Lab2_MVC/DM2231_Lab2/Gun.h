#pragma once
#include "vector3D.h"
#include <vector>
#include <string>
#include "Header.h"

#include <iostream>
using namespace std;


#ifndef CGUN_H
#define CGUN_H

class CGun
{
private:
	std::vector<unsigned int> frames;
	unsigned int Overview;
	//may not use
	unsigned int normalAnimation;
	unsigned int reloadAnimation;
	unsigned int fireAnimation;
	//precision - bullet may not always go straight
	float Precision;
	float aimPrecision;
	//Damage from Gun
	int DamageG;
	//flags
	bool isaim, isreload, isautomatic, isfired, istest;
	//Bullets
	unsigned int maxBulletsInMag;
	unsigned int bulletsInMag;
	unsigned int allBullets;

	unsigned int lastShot;
	unsigned int speed;

	unsigned int curframe;
	unsigned int curmode;

	std::string name;
	
public:
	CGun();
	~CGun();
	CGun(std::vector<unsigned int>& anim, unsigned int ol, unsigned int na, unsigned int ra, unsigned int fa
								,int dam, int maxb, int allb, int spd, const char* n, float prec, float aprec, bool isauto);
	void Update();
	void Show();

	//firing 
	bool Fire(/*Vector3D<float> Direction, Vector3D<float>camDirection*/);
	void stopFire();
	//reloading
	void Reload();

	void addBullets(unsigned int num);
	void setBullet(unsigned int num);

	int getDamageG();
	int getAmmo();
	int getAllAmmo();
	std::string getName();
	std::vector<unsigned int>& getAnimation();
	bool isAimed();
	unsigned int getOverview();

	//Rendering of Guns
	void renderPistol();
	void renderUzi();
	void renderShotgun();
	
	//temporary class
	void Keyboard(unsigned char key, int x, int y);
	
};
#endif 