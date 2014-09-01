#pragma once
class State
{
public:

	State(void);
	~State(void);

	enum states{start, menu, level, win, defeat, shop, credit};
	int theState;
	
};

