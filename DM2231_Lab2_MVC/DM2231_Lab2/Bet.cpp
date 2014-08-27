#include "Bet.h"


Bet::Bet(void)
{
	firstbet = true;
}


Bet::~Bet(void)
{
}

int Bet::BetEvent(int BetAmount)
{
	if(firstbet)
	{
		return BetAmount * 10;
	}
	else
	{
		return BetAmount * -1;
	}
}
