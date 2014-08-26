#include "Timer.h"


CTimer::CTimer(void)
{

}


CTimer::~CTimer(void)
{
}

void CTimer::start()
{
	startTime = clock();
}

unsigned long CTimer::elapsedTime()
{
	return ((unsigned long)clock() - startTime) / CLOCKS_PER_SEC;
}

bool CTimer::isTimeout(unsigned long seconds)
{
	return seconds >= elapsedTime();
}
