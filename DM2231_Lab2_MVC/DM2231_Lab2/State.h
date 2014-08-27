#pragma once
class State
{
public:

	State(void);
	~State(void);

	enum states{start, menu, level, tutorial, win, defeat, shop, bet, message, credit};
	int theState;
	
};

