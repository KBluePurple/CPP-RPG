#include "Time.h"
#include <chrono>

Time::Time()
{
	_startTime = clock();
}

Time::~Time()
{
}

float Time::GetTime()
{
	return clock() - _startTime;
}

float Time::GetStartTime()
{
	return _startTime;
}

void Time::Reset()
{
	_startTime = clock();
}
