#include <io.h>
#include <fcntl.h>
#include "Console.h"

bool Console::IsUTF8 = false;
Vector2 Console::Scale = Vector2(0, 0);
HANDLE Console::StdOutHandle = NULL;

void Console::SetTextColor(Color color)
{
	SetColor(color, true);
}

void Console::SetBackgroundColor(Color color)
{
	SetColor(color, false);
}

void Console::ResetColor(bool foreground, bool background)
{
	if (foreground)
	{
		SetColor(Color::DefaultForgroundColor, true);
	}
	if (background)
	{
		SetColor(Color::DefaultBackgroundColor, false);
	}
}

Vector2 Console::GetScale()
{
	if (Scale != Vector2(0, 0))
	{
		return Scale;
	}
	else
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		Vector2 consoleScale(0, 0);

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		consoleScale.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		consoleScale.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		Scale = consoleScale;

		return consoleScale;
	}
}

void Console::SetScale(Vector2 scale)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { (short)scale.x, (short)scale.y });
}

Vector2 Console::GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	Vector2 position(0, 0);

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	position.x = csbi.dwCursorPosition.X;
	position.y = csbi.dwCursorPosition.Y;

	return position;
}

COORD coord = {};
void Console::SetCursorPosition(Vector2 position)
{
	coord.X = position.x;
	coord.Y = position.y;
	SetConsoleCursorPosition(StdOutHandle, coord);
}

void Console::Clear()
{
	SetCursorPosition({ 0, 0 });
	SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << GetScale().x << ", " << GetScale().y;
	for (int i = 0; i < GetScale().y; i++)
	{
		cout << string(GetScale().x, ' ');
	}
	SetScale(GetScale());
	SetCursorPosition({ 0, 0 });
}

void Console::Pause()
{
	_getch();
}

void Console::SetUTF8(bool utf8)
{
	if (utf8)
		Console::IsUTF8 = _setmode(_fileno(stdout), _O_U16TEXT);
	else
		Console::IsUTF8 = !_setmode(_fileno(stdout), _O_TEXT);
}

void Console::Initialize()
{	
	HWND hwnd = GetConsoleWindow();
	StdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hInConsole = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_FONT_INFOEX cfi = {};
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	DWORD dwMode;
	GetConsoleMode(StdOutHandle, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(StdOutHandle, dwMode);

	SetTextColor(Color::DefaultForgroundColor);
	SetBackgroundColor(Color::DefaultBackgroundColor);

	LONG Style = GetWindowLong(hwnd, GWL_STYLE);
	SetWindowLong(hwnd, GWL_STYLE, Style & ~WS_TILEDWINDOW);

	::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);

	GetConsoleMode(hInConsole, &dwMode);
	dwMode |= ENABLE_WINDOW_INPUT;
	dwMode |= ENABLE_MOUSE_INPUT;
	dwMode &= ~ENABLE_EXTENDED_FLAGS;
	dwMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hInConsole, dwMode);

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	SetConsoleOutputCP(949);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(StdOutHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(StdOutHandle, &cursorInfo);

	::ShowCursor(false);
	auto scale = GetScale();
	SetScale(scale);
}

void Console::AlignedPrint(TextAlign align, string format, ...)
{
	va_list args;
	va_start(args, format);
	char buffer[1024];
	vsprintf_s(buffer, format.c_str(), args);
	va_end(args);

	Vector2 scale = GetScale();
	Vector2 position = GetCursorPosition();
	Vector2 size = { static_cast<int>(strlen(buffer)) - 1, 1 };

	switch (align)
	{
	case TextAlign::Left:
		break;
	case TextAlign::Center:
		position.x = (scale.x - size.x) / 2;
		break;
	case TextAlign::Right:
		position.x = scale.x - size.x;
		break;
	}

	SetCursorPosition(position);
	fprintf(stdout, buffer);
}

void Console::AlignedPrint(TextAlign align, wstring format, ...)
{
	va_list args;
	va_start(args, format);
	wchar_t buffer[1024];
	vswprintf_s(buffer, format.c_str(), args);
	va_end(args);

	Vector2 scale = GetScale();
	Vector2 position = GetCursorPosition();
	Vector2 size = { static_cast<int>(WideCharToMultiByte(CP_ACP, 0, buffer, - 1, NULL, 0, NULL, NULL)) - 1, 1 };

	switch (align)
	{
	case TextAlign::Left:
		break;
	case TextAlign::Center:
		position.x = (scale.x - size.x) / 2;
		break;
	case TextAlign::Right:
		position.x = scale.x - size.x;
		break;
	}

	SetCursorPosition(position);
	Console::SetUTF8(true);
	fwprintf(stdout, buffer);
	Console::SetUTF8(false);
}

Vector2 Console::GetCenter(Vector2 background, Vector2 foreground)
{
	Vector2 center = { 0, 0 };

	center.x = (background.x - foreground.x) / 2;
	center.y = (background.y - foreground.y) / 2;

	return center;
}

void Console::SetColor(Color color, bool isForeground)
{
	if (IsUTF8)
		wcout << L"\033[" << (isForeground ? 38 : 48) << L";2;" << color.r << L";" << color.g << L";" << color.b << L"m";
	else
		cout << "\033[" << (isForeground ? 38 : 48) << ";2;" << color.r << ";" << color.g << ";" << color.b << "m";
}
