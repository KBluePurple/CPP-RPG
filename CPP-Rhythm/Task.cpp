#include "Task.h"

Task::Task()
{
	_time.Reset();
	_isRunning = false;
}

void Task::Run()
{
	_isRunning = true;
	_time.Reset();
	while (_isRunning)
	{
		for (Generator<int> *task : _tasks)
		{
			if (task->operator()() == -1)
			{
				_isRunning = false;
				for (Generator<int>* task : _tasks)
				{
					delete task;
				}
			}
		}
		while (clock() - _time.GetStartTime() < 1)
		for (Generator<int> *task : _tasks)
		{
			task->delay -= clock() - _time.GetStartTime();
		}
		_time.Reset();
	}
}

void Task::Add(Generator<int> task)
{
	_tasks.push_back(&task);
}
