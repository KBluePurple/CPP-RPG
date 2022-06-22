#include "Note.h"
#include "Console.h"
const int offsetX = 20;
const int offsetY = 0;

const int noteWidth = 15;

Note::Note(int type, int line, int time, int offset)
{
	this->type = type;
	this->line = line;
	this->time = time;
	this->Position.x = offsetX + line * noteWidth;
	this->Position.y = offsetY;
	this->offset = offset;

	str = "";
	for (int i = 0; i < noteWidth; i++)
	{
		str += " ";
	}
}

Note::~Note()
{
}

void Note::Update(float deltaTime)
{
	deltaTime *= 0.001f;

	Position.y += deltaTime * ((1000.0f / (float)offset) * 46);

	newPos = Position.ToVector2();

	if (this->Position.y > 54)
	{
		IsDead = true;
		Destroy();
	}
}

void Note::Render()
{
}

void Note::Render(Color color)
{
	if (IsDead) return;

	if (prevPos == newPos) return;

	if (this->Position.y != 50)
	{
		Console::SetCursorPosition(prevPos);
		Console::Write(str);
	}

	Console::SetCursorPosition(newPos);
	Console::SetBackgroundColor(color);
	Console::Write(str);
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);

	prevPos = newPos;
}

void Note::Destroy()
{
	if (this->Position.y != 50)
	{
		Console::SetCursorPosition(prevPos);
		Console::Write(str);
	}
}
