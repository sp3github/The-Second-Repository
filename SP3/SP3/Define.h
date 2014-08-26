#pragma once
//Headers
#include "vector3D.h"
#include "Obstacle.h"
#include "Gun.h"
#include "Zombies.h"

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <vector>

using namespace std;

//GUN
#define PISTOL 1
#define SHOTGUN 2
#define UZI 3

//ZOMBIE

#define NORMAL 4
#define FAST 5 
#define SLOW 6

//**************************************
//NOTES
//**************************************
//Rof = Rate Of Fire
//Merge with Entity Class
//lastShot = how many frame ago did we shoot the weapon
//speed = how many frame we need to shot the weapon