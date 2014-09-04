#pragma once
class State
{
public:

	State(void);
	~State(void);

	enum states{EnterName, storyins ,menu, level,PageToLearnShop,  shop , win, defeat, credit, subpagelevel };
	int theState;
	
};

