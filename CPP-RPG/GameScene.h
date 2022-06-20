#pragma once
#include "Scene.h"
class GameScene : public Scene
{
public:
	void Initialize() override;
	void Run() override;
	void PrintInfo();
	void PrintMap(int);
};

