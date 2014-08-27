//#include "Zombies.h"
//
//CZombies::CZombies(void)
//{
//
//}
//CZombies::~CZombies(void)
//{
//
//}
//CZombies::CZombies(std::vector<unsigned int> anim,
//				   unsigned int w, unsigned int a, unsigned int d, 
//				   int h, int str, float spd/*, collisionsphere css*/)
//{
//	frames = anim;
//	walk = w;
//	attack = a;
//	die = d;
//	health = h;
//	strength = str;
//	speed = spd;
//	//cs = css;
//
//	iswalk = true;
//	isattack = false;
//	isdead = false;
//}
//bool CZombies::Update(/*std::vector<collision plane>& col,*/ vector3D playerLoc)
//{
//	if (!isdead)
//	{
//		direction.change(playerLoc - cs.center);
//		direction.Normalize();
//
//		vector3D newpos(cs.center);
//		newpos.y -= 0.3; //gravity
//		newpos += direction*speed;
//		for (int i = 0; i < col.size()++; i++)
//		{
//			//collision::sphereplane(newpos,col[i].normal,col[i].p[0],col[i].p[1],col[i].p[2],col[i].p[3],cs.r);
//			setLocation(newpos);
//		}
//		rotation.y = std::acos(direction.z);
//		if (direction.x > 0)
//		{
//			rotation.y = -rotation.y;
//		}
//	}
//	if (health <= 0 && !isdead)
//	{
//		isdead = true;
//		iswalk = false;
//		isattack = false;
//		curframe = walk + attack;
//		return true;
//	}
//	curframe++;	
//	if (iswalk && curframe >= walk)
//	{
//		curframe = 0;
//	}
//	else if (isattack && curframe >= walk+attack)
//	{
//		curframe = walk;
//	}
//	else if (isdead && curframe >= walk+attack+die)
//	{
//		curframe = walk+attack+die - 1;
//	}
//	return false;
//}
//void CZombies::show() //show zombie
//{
//
//}
//bool CZombies::setAttack(/*collisionpshere player*/)
//{
//	if (collisionsphere::spheresphere(player, cs))
//	{
//		isattack = true;
//		iswalk = false;
//		return true;
//	}
//	else 
//	{
//		isattack = false;
//		iswalk = true;
//		return false;
//	}
//}
///*collisionsphere* CZombies::getCollisonSphere()
//{
//
//}*/
//void CZombies::setLocation(vector3D newloc)
//{
//	cs.center = loc;
//}
//void CZombies::deceasingHealth(int num)
//{
//	health = num;
//}
//int CZombies::getHealth()
//{
//	return health;
//}
//int CZombies::getStrength()
//{
//	return strength;
//}
//bool CZombies::isDead()
//{
//	return isdead;
//}