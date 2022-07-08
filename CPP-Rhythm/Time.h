#pragma once

class Time
{
public:
	Time();
	~Time();
	float GetTime();
	float GetStartTime();
	void Reset();

private:
	float _startTime;
};

