#pragma once
#include "Define.h"
#include "Obstacle.h"

#ifndef CBUILDING_H
#define CBUILDING_H

class Building : public CObstacle
{
public:
	Building(void);
	~Building(void);
};
#endif

