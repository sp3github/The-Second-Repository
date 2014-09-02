#pragma once

class CMoney
{
private:
	int money;
public:
	CMoney(void);
	~CMoney(void);

	int playerMoney;
	
	void AddMoney(int addIn);
};

