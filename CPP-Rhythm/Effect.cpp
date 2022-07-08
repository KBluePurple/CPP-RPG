#include "Effect.h"
#include "Console.h"

Effect::Effect()
{
	startColor = { 0, 0, 0 };
	endColor = { 0, 0, 0 };
	line = 0;
	time = 0;
}

Effect::Effect(Color startColor, Color endColor, int line, float time)
{
	this->startColor = startColor;
	this->endColor = endColor;
	this->line = line;
	this->time = time;
	IsEnded = false;
}

void Effect::Update(float dt)
{
	if (time > 0)
	{
		if (startColor != endColor)
		{
			float r = (endColor.r - startColor.r) / time;
			float g = (endColor.g - startColor.g) / time;
			float b = (endColor.b - startColor.b) / time;
			time -= dt;
			startColor.r += r * dt;
			startColor.g += g * dt;
			startColor.b += b * dt;
		}
		else
		{
			time -= dt;
		}
	}

	if (time <= 0)
	{
		IsEnded = true;
	}
}

void Effect::Render()
{
	switch (line)
	{
	case 0:
		Console::SetCursorPosition({ 20, 45 });
		break;
	case 1:
		Console::SetCursorPosition({ 35, 45 });
		break;
	case 2:
		Console::SetCursorPosition({ 50, 45 });
		break;
	case 3:
		Console::SetCursorPosition({ 65, 45 });
		break;
	default:
		break;
	}

	Console::SetBackgroundColor(startColor);
	Console::Write("               ");
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
}

void Effect::Destroy()
{
}
