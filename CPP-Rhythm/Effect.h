#pragma once
#include "GlobalStd.h"
#include "GameObject.h"

class Effect : GameObject
{
public:
	Effect();
	Effect(Color startColor, Color endColor, int line, float time);
	
private:
	Color startColor;
	Color endColor;

public:
	int line;
	bool IsEnded;
	float time;

	void Update(float dt) override;
	void Render() override;
	void Destroy() override;
};

