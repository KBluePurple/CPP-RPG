#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	void Initialize() override;
	void Run() override;

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;
};

