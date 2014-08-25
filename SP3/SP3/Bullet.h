#pragma once
#include "Define.h"
#ifndef CBULLET_H
#define CBULLET_H
class CBullet
{
private:
	int DamageB;
public:
	CBullet(void);
	~CBullet(void);

	void ChangeBulletType();

};
#endif
