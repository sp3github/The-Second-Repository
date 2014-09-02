#include "Money.h"


CMoney::CMoney(void)
{
	playerMoney = 0;
}


CMoney::~CMoney(void)
{
}

void CMoney::AddMoney(int addIn)
{
	playerMoney = addIn + playerMoney;
}