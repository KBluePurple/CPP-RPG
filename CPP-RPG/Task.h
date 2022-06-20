#pragma once
#include "Generator.h"
#include "Time.h"

class Task
{
public:
	Task();
	void Run();
	void Add(Generator<int> task);
private:
	vector<Generator<int>*> _tasks;
	Time _time;
	bool _isRunning;
};