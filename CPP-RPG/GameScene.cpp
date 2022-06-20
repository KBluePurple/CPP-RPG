#include "GameScene.h"
#include "Global.h"

Vector2 MapSize = Vector2(12, 8);
Vector2 TileSize = Vector2(8, 4);

Vector2 ItemNamePos = Vector2(0, 3);
Vector2 ItemDescPos = Vector2(0, 5);

Vector2 DesignationPos = Vector2(47, 3);
Vector2 HealthPos = Vector2(47, 5);

Vector2 DeathCountPos = Vector2(145, 5);

Rect MapCanvasRect = Rect(48, 9, 60, 98);

void PrintItemName(wstring str)
{
	Console::SetCursorPosition(ItemNamePos);
	Console::AlignedPrint(TextAlign::Center, str);
}

void PrintItemDesc(wstring str)
{
	Console::SetCursorPosition(ItemDescPos);
	Console::AlignedPrint(TextAlign::Center, str);
}

void PrintDesignation(wstring str)
{
	Console::SetCursorPosition(DesignationPos);
	Console::SetUTF8(true);
	wcout << L"칭호: " << str;
	Console::SetUTF8(false);
}

void PrintHealth(int health)
{
	Console::SetCursorPosition(HealthPos);
	Console::SetUTF8(true);
	wcout << L"체력: ";
	for (int i = 0; i < 20; i++)
	{
		if (i < health)
			wcout << L"█";
		else
			wcout << L"░";
	}
	Console::SetUTF8(false);
}

void PrintDeathCount(int count)
{
	wstring str = L"사망 횟수: " + to_wstring(count);

	int strSize = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);

	Console::SetCursorPosition({ DeathCountPos.x - strSize, DeathCountPos.y });
	Console::SetUTF8(true);
	wcout << str;
	Console::SetUTF8(false);
}

void PrintMold()
{
	int moldSize = 99;
	int line = 8;
	
	Console::SetUTF8(true);
	
	Vector2 pos = Console::GetCenter(Console::Scale, { 99, 0 });
	wstring str = L"";

	str.append(L"┌");
	for (int i = 0; i < moldSize - 2; i++)
	{
		str.append(L"─");
	}
	str.append(L"┐\n");
	Console::SetCursorPosition({ pos.x, line++ });
	wcout << str;
	str = L"";
	for (int i = 0; i < 32; i++)
	{
		str.append(L"│");
		for (int i = 0; i < moldSize - 2; i++)
		{
			str.append(L" ");
		}
		str.append(L"│\n");
		Console::SetCursorPosition({ pos.x, line++ });
		wcout << str;
		str = L"";
	}
	str.append(L"┝");
	for (int i = 0; i < moldSize - 2; i++)
	{
		str.append(L"━");
	}
	str.append(L"┥\n");
	Console::SetCursorPosition({ pos.x, line++ });
	wcout << str;
	str = L"";
	for (int i = 0; i < 10; i++)
	{
		str.append(L"│");
		for (int i = 0; i < moldSize - 2; i++)
		{
			str.append(L" ");
		}
		str.append(L"│\n");
		Console::SetCursorPosition({ pos.x, line++ });
		wcout << str;
		str = L"";
	}
	str.append(L"└");
	for (int i = 0; i < moldSize - 2; i++)
	{
		str.append(L"─");
	}
	str.append(L"┘");
	Console::SetCursorPosition({ pos.x, line++ });
	wcout << str;
	str = L"";
	Console::SetUTF8(false);
}

void GameScene::PrintInfo()
{
	PrintItemName(L"『낡은 철문』");
	PrintItemDesc(L"[F] 키를 눌러 상호작용");
	PrintDesignation(L"착할뻔한 용사");
	PrintHealth(10);
	PrintDeathCount(10);
}

void GameScene::PrintMap(int offset)
{
	Vector2 MapPos = Vector2(MapCanvasRect.x, MapCanvasRect.y);
	
	for (int i = 0; i < MapSize.y; i++)
	{
		for (int j = 0; j < MapSize.x; j++)
		{
			Console::SetBackgroundColor({ (j + i + offset) * 10 % 255, (j + i + offset) * 10 % 255, (j + i + offset) * 10 % 255 });
			for (int k = 0; k < 4; k++)
			{
				Console::SetCursorPosition({ MapPos.x + j * 8, MapPos.y + i * 4 + k });
				printf("        ");
			}
		}
	}
}
Vector2 PlayerPos = Vector2(0, 0);
void PrintPlayer(int key, Vector2 pos)
{
	Console::SetUTF8(true);
	Console::SetCursorPosition(pos);
	switch (key)
	{
	case 'a':
		wprintf(L"  △△  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 1 });
		wprintf(L" ('◦ ') \n");
		Console::SetCursorPosition({ pos.x, pos.y + 2 });
		wprintf(L"  |  |  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 3 });
		wprintf(L"  ▽▽  \n");
		break;
	case 'd':
		wprintf(L"  △△  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 1 });
		wprintf(L" (' ◦') \n");
		Console::SetCursorPosition({ pos.x, pos.y + 2 });
		wprintf(L"  |  |  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 3 });
		wprintf(L"  ▽▽  \n");
		break;
	case 'w':
		wprintf(L"  △△  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 1 });
		wprintf(L" (    ) \n");
		Console::SetCursorPosition({ pos.x, pos.y + 2 });
		wprintf(L"  |  |  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 3 });
		wprintf(L"  ▽▽  \n");
		break;
	case 's':
		wprintf(L"  △△  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 1 });
		wprintf(L" (- ◦-) \n");
		Console::SetCursorPosition({ pos.x, pos.y + 2 });
		wprintf(L"  |  |  \n");
		Console::SetCursorPosition({ pos.x, pos.y + 3 });
		wprintf(L"  ▽▽  \n");
		break;
	}
	Console::SetUTF8(false);
}

void GameScene::Initialize()
{
	PrintMold();
	PrintInfo();
}

void GameScene::Run()
{
	while (true)
	{
		int key = _getch();
		PrintPlayer(key, { MapCanvasRect.x + TileSize.x * PlayerPos.x, MapCanvasRect.y + TileSize.y * PlayerPos.y });
	}
}
