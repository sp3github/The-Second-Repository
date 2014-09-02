#include "Money.h"


CMoney::CMoney(void)
{
	playerMoney = 0;
	money = 50;
}


CMoney::~CMoney(void)
{
}

void CMoney::AddMoney(int addIn)
{
	addIn = money;
	playerMoney = addIn + playerMoney;

}