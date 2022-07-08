#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	void Initialize() override;
	void Run() override;

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};

