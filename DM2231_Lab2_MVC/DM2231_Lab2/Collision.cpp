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

bool Collision::CheckCollision(CEntity *go, CEntity *other, bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft , bool m_bCheckRight )
{
	if(go->movementspeed == 0)
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
	Atile_left_x = go->GetX();
	Atile_right_x = go->GetX() + go->tile_size; 
	Atile_top_y =  go->GetY() ; 
	Atile_bottom_y = go->GetY() + go->tile_size;

	//Check against other entities.
	if(other == NULL)
	{
		//Now check if move against wall
	if(m_bCheckUpwards)
		return WallCollision( Atile_left_x, Atile_right_x, Atile_top_y - go->movementspeed, Atile_bottom_y - go->movementspeed);
	if(m_bCheckDownwards)
		return WallCollision( Atile_left_x, Atile_right_x, Atile_top_y + go->movementspeed, Atile_bottom_y + go->movementspeed);
	if(m_bCheckLeft)
		return WallCollision( Atile_left_x - go->movementspeed, Atile_right_x - go->movementspeed, Atile_top_y, Atile_bottom_y);
	if(m_bCheckRight)
		return WallCollision( Atile_left_x + go->movementspeed, Atile_right_x + go->movementspeed, Atile_top_y, Atile_bottom_y);
	}
	else
	{
		Btile_left_x = other->GetX();
		Btile_right_x = other->GetX() + other->tile_size; 
		Btile_top_y =  other->GetY() ; 
		Btile_bottom_y = other->GetY()+ other->tile_size;


		if(!(Btile_left_x > Atile_right_x
			|| Btile_right_x < Atile_left_x
			|| Btile_top_y > Atile_bottom_y
			|| Btile_bottom_y < Atile_top_y ))
		{
			cout<<"COLLIDED"<<endl;
			return true;
		}
	}

	



}

bool Collision::WallCollision(int left, int right, int top, int bottom)
{
	if(Collider(left,top))
	{
		return false;
	}
	if(Collider(left, bottom))
	{
		return false;
	}
	if(Collider(right, top))
	{
		return false;
	}
	if(Collider(right, bottom))
	{
		return false;
	}

	return true;
}

bool Collision::Collider(int x, int y)
{
	if(theMap->theScreenMap[(y + theMap->mapOffset_y) / TILE_SIZE][(x + theMap->mapOffset_x) / TILE_SIZE] != 0)
	{
		return true;
	}

	return false;
}