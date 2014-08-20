#pragma once
<<<<<<< HEAD
#include <vector>
=======
#include "Map.h"
#include "Ortho2D.h"
>>>>>>> origin/master
#include <stdio.h>
#include "Entity.h"

class DM2231_Model
{
public:
	DM2231_Model(void);
	~DM2231_Model(void);
	// Update the model
	void Update(void);
<<<<<<< HEAD
	std::vector<CEntity> theArrayOfEntities;
=======
	CMap TestMap;
	Ortho2D theOrtho2DSetUp;
	

>>>>>>> origin/master
};
