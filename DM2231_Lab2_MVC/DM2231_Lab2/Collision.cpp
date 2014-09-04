#include "Collision.h"
#include "Header.h"

Collision::Collision(void)
{
}

Collision::Collision(CMap & theMap,vector<CEntity*> & theArray)
{
	this->theMap = &theMap;
	this->theArray = &theArray;
}

Collision::~Collision(void)
{
}

bool Collision::CheckCollision(CEntity *go, CEntity *other, bool m_bCheckUpwards, bool m_bCheckDownwards, bool m_bCheckLeft , bool m_bCheckRight, bool CheckPos )
{
	//if true, not colliding. if false, collided.
	if(go->movementspeed == 0)
		return true;
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


	//Check against other entities.
	if(other == NULL)
	{
		
		Atile_left_x = go->GetX();
	Atile_right_x = go->GetX() + go->tile_size; 
	Atile_top_y =  go->GetY() ; 
	Atile_bottom_y = go->GetY() + go->tile_size;

		//Now check if move against wall
	if(m_bCheckUpwards)
		return WallCollision( Atile_left_x, Atile_right_x, Atile_top_y - go->movementspeed, Atile_bottom_y - go->movementspeed);
	if(m_bCheckDownwards)
		return WallCollision( Atile_left_x, Atile_right_x, Atile_top_y + go->movementspeed, Atile_bottom_y + go->movementspeed);
	if(m_bCheckLeft)
		return WallCollision( Atile_left_x - go->movementspeed, Atile_right_x - go->movementspeed, Atile_top_y, Atile_bottom_y);
	if(m_bCheckRight)
		return WallCollision( Atile_left_x + go->movementspeed, Atile_right_x + go->movementspeed, Atile_top_y, Atile_bottom_y);
	if(CheckPos)
		return WallCollision(Atile_left_x, Atile_right_x, Atile_top_y, Atile_bottom_y);
	}

	else if ((go->ID == PLAYER && other->ID != BULLET) || (go->ID == BULLET && other->ID != PLAYER) || (go->ID == ZOMBIE) || (go->ID == SPZOMBIE))
	{
		if (go->ID == ZOMBIE || go->ID == SPZOMBIE)	//Check Zombies with mapoffset against others with mapoffset
		{
			Vector3D<float> dir (0,0,0);
			Vector3D<float> BDir (0,0,0);
			if(go->vel.Magnitude()!= 0)
				dir = go->vel.Normalized();
			if(other->vel.Magnitude() != 0)
				BDir = other->vel.Normalized();

			Atile_left_x = go->GetX() - theMap->mapOffset_x + dir.x;
			Atile_right_x = go->GetX() + go->tile_size - theMap->mapOffset_x + dir.x;
			Atile_top_y = go->GetY() - theMap->mapOffset_y + dir.y;
			Atile_bottom_y = go->GetY() + go->tile_size - theMap->mapOffset_y +dir.y;

			Btile_left_x = other->GetX() - theMap->mapOffset_x  + BDir.x;
			Btile_right_x = other->GetX() + other->tile_size - theMap->mapOffset_x + BDir.x;
			Btile_top_y = other->GetY() - theMap->mapOffset_y + BDir.y;
			Btile_bottom_y = other->GetY() + other->tile_size - theMap->mapOffset_y + BDir.y;
		}
		else//Player collision
		{
			Atile_left_x = go->GetX() ;
			Atile_right_x = go->GetX() + go->tile_size;
			Atile_top_y = go->GetY(); 
			Atile_bottom_y = go->GetY() + go->tile_size ;

			Btile_left_x = other->GetX() - theMap->mapOffset_x;
			Btile_right_x = other->GetX() + other->tile_size - theMap->mapOffset_x;
			Btile_top_y = other->GetY() - theMap->mapOffset_y;
			Btile_bottom_y = other->GetY() + other->tile_size - theMap->mapOffset_y;
		}


		if(!(Btile_left_x > Atile_right_x
			|| Btile_right_x < Atile_left_x
			|| Btile_top_y > Atile_bottom_y
			|| Btile_bottom_y < Atile_top_y ))
		{
 			return false;
		}
	}
	return true;

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
	if(x > theMap->getNumOfTiles_ScreenWidth()  * TILE_SIZE|| y > theMap->getNumOfTiles_ScreenHeight() * TILE_SIZE)
		return true;
	if( x < 0 || y < 0)
		return true;
	int MapArea = theMap->theScreenMap[(y + theMap->mapOffset_y) / TILE_SIZE][(x + theMap->mapOffset_x) / TILE_SIZE];
	if(MapArea == 1 || MapArea == 10)
	{
		return true;
	}
	return false;
}