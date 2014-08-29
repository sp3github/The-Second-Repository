#include "Gun.h"

CGun::CGun()
{

}

CGun::~CGun()
{

}

CGun::CGun(std::vector<unsigned int>& anim, unsigned int ol, unsigned int na, unsigned int ra, unsigned int fa
								,int dam, int maxb, int allb, int spd, const char* n, float prec, float aprec, bool isauto)
{
		frames = anim;
		Overview = ol;
		normalAnimation = na;
		reloadAnimation = ra;
		fireAnimation = fa;
		Precision = (prec != 0 ? prec : 0.000001);
		aimPrecision = (aprec != 0 ? aprec : 0.00001);
		DamageG = dam;	
		allBullets = allb;
		maxBulletsInMag = maxb;
		speed = spd;
		name = n;

		isaim = false;
		isreload = false;
		isautomatic = isauto;
		isfired = false;
		istest = false;
		bulletsInMag = maxBulletsInMag;
		lastShot = 1000;

		curframe = 0;
		curmode = 1;
}

void CGun::Update()
{
	//test();
	lastShot++;// 10 + 1
	curframe++;

	if (curmode == 1)
	{
		if (curframe >= normalAnimation)
		{
			curframe = 0;
		}
		else if (curmode = 2)
		{
			if (curframe >= normalAnimation + fireAnimation)
			{
				if (isautomatic && isfired)
				{
					curframe = normalAnimation;
				}
				else
				{
					curmode = 1;
					curframe = 0;
				}
			}
		}
		else if (curmode = 3)
		{
			if (curframe >= normalAnimation + fireAnimation + reloadAnimation)
			{
				curmode = 1;
				curframe = 0;
				isreload = false;
			}
		}
	}
}

void CGun::Show()
{
	int tile_size = 24;
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(300,100, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glScalef(3,3,3);
	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(0, 0);
	glTexCoord2f(0, 0); glVertex2f(0, tile_size);
	glTexCoord2f(1, 0); glVertex2f(tile_size, tile_size);
	glTexCoord2f(1, 1); glVertex2f(tile_size, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	cout << "OKOKOK" << endl;
}

bool CGun::Fire(/*Vector3D<float> Direction, Vector3D<float> camDirection*/)
{
	if (isreload)
		return false;
	if ( (!isautomatic && !isfired) || isautomatic)
	{
		if (lastShot >= speed)
		{
			if (bulletsInMag > 0)
			{
				/*if (isaim)
				{
					Direction.x = camDirection.x + ((float)(rand()%3 - 1) / aimPrecision);	
					Direction.y = camDirection.y + ((float)(rand()%3 - 1) / aimPrecision);	
					Direction.z = camDirection.z + ((float)(rand()%3 - 1) / aimPrecision);	
				}
				else 
				{
					Direction.x = camDirection.x + ((float)(rand()%3 - 1) / Precision);	
					Direction.y = camDirection.y + ((float)(rand()%3 - 1) / Precision);	
					Direction.z = camDirection.z + ((float)(rand()%3 - 1) / Precision);	
				}*/
				//cout << "success" << endl;
				isfired = true;
				lastShot = 0;
				bulletsInMag--;
				curframe = normalAnimation;
				return true;
			}
			else 
			{
				Reload();
				return false;
			}
		}
	}
	return false;
}

void CGun::stopFire()
{
	isfired = false;
}

void CGun::Reload()
{
	if (!isreload && maxBulletsInMag != bulletsInMag)
	{
		isreload = true;
		if (allBullets > maxBulletsInMag - bulletsInMag)
		{
			allBullets -= maxBulletsInMag - bulletsInMag;
			bulletsInMag = maxBulletsInMag;
		}
		else 
		{
			bulletsInMag = allBullets + bulletsInMag;
			allBullets = 0;
		}

		curframe = normalAnimation + fireAnimation;
		curmode = 3;
	}
}

void CGun::addBullets(unsigned int num)
{
	allBullets += num;
}

void CGun::setBullet(unsigned int num)
{
	allBullets = num;
}

int CGun::getDamageG()
{
	return DamageG;
}

int CGun::getAmmo()
{
	return bulletsInMag;
}

int CGun::getAllAmmo()
{
	return allBullets;
}

string CGun::getName()
{
	return name;
}

std::vector<unsigned int>& CGun::getAnimation()
{
	return frames;
}

bool CGun::isAimed()
{
	return isaim;
}

unsigned int CGun::getOverview()
{
	return Overview;
}

//Rendering of Guns
void CGun::renderPistol()
{

}

void CGun::renderUzi()
{

}

void CGun::renderShotgun()
{

}

//temporary class
void CGun::Keyboard(unsigned char key, int x, int y)
{
	/*keyState[key] = BUTTON_DOWN;

	switch(key)
	{
	case '1':
		cout << "Pistol" << endl;
		break;
	}*/
}
