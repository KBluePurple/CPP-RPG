#pragma once

#include "Global.h"

enum class TextAlign
{
	Left,
	Center,
	Right
};

static class Console
{
public:
	static bool IsUTF8;
	
public:
	static void SetTextColor(Color color);
	static void SetBackgroundColor(Color color);
	
	static void ResetColor(bool foreground = true, bool background = false);
	
	static Vector2 GetScale();
	static void SetScale(Vector2 scale);
	
	static Vector2 GetCursorPosition();
	static void SetCursorPosition(Vector2 position);
	
	static void Clear();
	static void Pause();

	static void SetUTF8(bool utf8);

	static void Initialize();

	static void AlignedPrint(TextAlign align, string format, ...);
	static void AlignedPrint(TextAlign align, wstring format, ...);

	static Vector2 GetCenter(Vector2 background, Vector2 foreground);
	
	static Vector2 Scale;
	
private:
	static void SetColor(Color color, bool isForeground);
	static HANDLE StdOutHandle;
};
