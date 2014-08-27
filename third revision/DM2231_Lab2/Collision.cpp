#include "Collision.h"
#include "Header.h"

Collision::Collision(void)
{
}

Collision::Collision(CMap & theMap)
{
	this->theMap = &theMap;
}

Collision::~Collision(void)
{
}

bool Collision::CheckCollision(CEntity go, CEntity other,bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft, bool m_bCheckRight)
{
	if(go.movementspeed == 0)
		return false;
	float Atile_left_x;
	float Atile_right_x;
	float Atile_bottom_y;
	float Atile_top_y;

	float Btile_left_x;
	float Btile_right_x;
	float Btile_bottom_y;
	float Btile_top_y;
	//Variables for the sides of the collision

	//Calculate the sides of rect A 
	Atile_left_x = go.GetX() - TILE_SIZE / 2;
	Atile_right_x = go.GetX() + TILE_SIZE / 2; 
	Atile_top_y =  go.GetY() + TILE_SIZE / 2; 
	Atile_bottom_y = go.GetY() - TILE_SIZE / 2;
	
	//Calculate the sides of rect B 
	Btile_left_x = other.GetX() - TILE_SIZE / 2;
	Btile_right_x = other.GetX() + TILE_SIZE / 2; 
	Btile_top_y =  other.GetY() + TILE_SIZE / 2; 
	Btile_bottom_y = other.GetY() - TILE_SIZE / 2;

	//For forward checking
	//if(m_bCheckUpwards)
	//{
	//	Atile_bottom_y += go.movementspeed;
	//	Atile_top_y += go.movementspeed;  


	//}
	//if(m_bCheckDownwards)
	//{
	//	Atile_bottom_y -= go.movementspeed;
	//	Atile_top_y -= go.movementspeed;  
	//}
	//if(m_bCheckLeft)
	//{
	//	Atile_left_x += go.movementspeed;
	//	Atile_right_x += go.movementspeed;

	//}
	//if(m_bCheckRight)
	//{
	//	Atile_left_x -= go.movementspeed;
	//	Atile_right_x -= go.movementspeed;
	//}

	//This checks against other entities.
	if(Atile_bottom_y <= Btile_top_y)
	{
		//COLLIDED
		return false;
	}
	if(Atile_top_y >= Btile_bottom_y)
	{
		//COLLIDED
		return false;
	}
	if(Atile_right_x <= Btile_left_x)
	{
		//COLLIDED
		return false;
	}
	if(Atile_left_x >= Btile_right_x)
	{
		//COLLIDED
		return false;
	}
	//Now check if move against wall
	
	//If none of the sides from A are outside B
	return WallCollision(go);
}

bool Collision::WallCollision(CEntity go)
{
	if(theMap->theScreenMap[go.GetX() + theMap->mapOffset_x][go.GetX() + theMap->mapOffset_x ] == 1)
	{
		return false;
	}
	return true;
}