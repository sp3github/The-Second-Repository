#pragma once

#include <ctime>

class CTimer
{
private:
	unsigned long startTime;
	
public:
	CTimer(void);
	~CTimer(void);

	void start();

	unsigned long elapsedTime();
	bool isTimeout(unsigned long seconds);
};

