#pragma once
#include <string>
class Bet
{
public:
	int BetEvent(int BetAmount);
	Bet(void);
	~Bet(void);
	std::string AmounttoBet;

	bool firstbet;
};

