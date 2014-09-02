#pragma once
class State
{
public:

	State(void);
	~State(void);

	enum states{subpage, menu, level, win, defeat, shop, credit, PageToLearnShop};
	int theState;
	
};

