#pragma once
#include "Map.h"
#include "Ortho2D.h"
#include "Mouse.h"
#include <stdio.h>

class DM2231_Model
{
public:
	DM2231_Model(void);
	~DM2231_Model(void);
	// Update the model
	void Update(void);
	CMap TestMap;
	Ortho2D theOrtho2DSetUp;
	CMouse theMouseInfo;

};
