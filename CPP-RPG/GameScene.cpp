#include "GameScene.h"
#include "GlobalStd.h"
#include "Console.h"

float fps = 0;

Color GameScene::ColorGradiant(int life)
{
	life = 100 - life;
	
	Color startColor = Color(171, 178, 191);
	Color endColor = Color(255, 0, 0);

	float ratio = (float)life / 100;

	int r = startColor.r + (endColor.r - startColor.r) * ratio;
	int g = startColor.g + (endColor.g - startColor.g) * ratio;
	int b = startColor.b + (endColor.b - startColor.b) * ratio;

	return Color(r, g, b);
}

void GameScene::Initialize()
{
	ifstream json_dir(mapFile);
	
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;

	Json::Value value;
	JSONCPP_STRING errs;

	int startTime = clock();

	if (parseFromStream(builder, json_dir, &value, &errs))
	{
		for (auto item : value["notes"])
		{
			notes.push_back(
				{
					item["type"].asInt(),
					item["line"].asInt(),
					item["time"].asInt(),
					item["endTime"].asInt()
				});
		}
	}
	else
	{
		cout << "Parse failed.: " << errs << endl;
	}

	musicAudio.Open(mp3File);

	lineColor[0] = Color::DefaultForgroundColor;
	lineColor[1] = { 66, 135, 245 };
	lineColor[2] = { 66, 135, 245 };
	lineColor[3] = Color::DefaultForgroundColor;

	musicTime = -offset;
	life = 100;

	for (int i = 0; i < 15; i++)
	{
		str += " ";
	}
}

void GameScene::Run()
{
	int prevTime = startTime;
	while (!IsEnded)
	{
		deltaTime = clock() - prevTime;
		if (deltaTime > 1000 / 144)
		{
			prevTime = clock();
			totalTime += deltaTime;
			Update();
			Render();
		}
	}
}

int GameScene::GetMusicTime()
{
	return musicTime + offset;
}

void GameScene::ComboBreak()
{
	combo = 0;
	life -= 5;
}

GameScene::GameScene(wstring mapName, wstring mp3File, string mapFile, int speed)
{
	this->mapName = mapName;
	this->mp3File = mp3File;
	this->mapFile = mapFile;
	this->offset = speed;
}

void GameScene::CheckLine(int line)
{
	for (int i = 0; i < noteObjects.size(); i++)
	{
		auto& noteObject = noteObjects[i];
		if (noteObject.line == line)
		{
			int diffTime = abs(noteObject.time - musicTime);

			if (diffTime < 18) // marvelous
			{
				ShowEffect(0, line);
				AddLife(1);
				score += 350;
				judgeStore[0]++;
			}
			else if (diffTime < 43) // perfect
			{
				ShowEffect(1, line);
				AddLife(1);
				score += 300;
				judgeStore[1]++;
			}
			else if (diffTime < 76) // great
			{
				ShowEffect(2, line);
				score += 100;
				judgeStore[2]++;
			}
			else if (diffTime < 106) // good
			{
				ShowEffect(3, line);
				score += 50;
				judgeStore[3]++;
			}
			else if (diffTime < 127) // okay
			{
				ShowEffect(4, line);
				score += 20;
				judgeStore[4]++;
			}
			else if (diffTime < 180) // miss
			{
				if (noteObject.time - musicTime < 0)
				{
					continue;
				}
				ShowEffect(5, line);
				ComboBreak();
				judgeStore[5]++;
			}
			else
			{
				return;
			}

			combo++;
			if (combo > maxCombo)
			{
				maxCombo = combo;
			}

			noteObject.Destroy();
			noteObjects.erase(noteObjects.begin() + i);

			break;
		}
	}
}

int testTime = 0;

void GameScene::Update()
{
	testTime = clock();
	fps = 1000.0f / deltaTime;

	int musicPos = musicAudio.GetPosition();
	if (life <= 0 || musicPos >= musicAudio.GetLength())
	{
		if (musicAudio.IsPlaying())
			musicAudio.Stop();
		IsEnded = true;
		musicAudio.Close();

		Console::Clear();

		Console::SetCursorPosition({ 0, 23 });
		Console::AlignedPrint(TextAlign::Center, mapName);
		Console::SetCursorPosition({ 0, 25 });
		Console::AlignedPrint(TextAlign::Center, L"Game Over");
		Console::SetCursorPosition({ 0, 27 });
		Console::AlignedPrint(TextAlign::Center, L"Score: " + to_wstring(score));
		Console::SetCursorPosition({ 0, 28 });
		Console::AlignedPrint(TextAlign::Center, L"Max Combo: " + to_wstring(maxCombo));

		Console::SetCursorPosition({ 91, 30 });
		Console::SetBackgroundColor({ 255, 255, 255 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Marv: " << judgeStore[0];
		Console::SetCursorPosition({ 91, 32 });
		Console::SetBackgroundColor({ 245, 197, 66 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Perf: " << judgeStore[1];
		Console::SetCursorPosition({ 91, 34 });
		Console::SetBackgroundColor({ 7, 199, 0 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Great: " << judgeStore[2];
		Console::SetCursorPosition({ 91, 36 });
		Console::SetBackgroundColor({ 0, 69, 173 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Good: " << judgeStore[3];
		Console::SetCursorPosition({ 91, 38 });
		Console::SetBackgroundColor({ 74, 74, 74 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Okay: " << judgeStore[4];
		Console::SetCursorPosition({ 91, 40 });
		Console::SetBackgroundColor({ 189, 0, 0 });
		cout << "  ";
		Console::SetBackgroundColor(Color::DefaultBackgroundColor);
		cout << " Miss: " << judgeStore[5];
		
		Console::SetCursorPosition({ 0, 42 });
		Console::AlignedPrint(TextAlign::Center, L"Press [ Enter ] to continue");
		
		while (true)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				break;
			}
		}

		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		int _ = _getch();
	}
	else if (musicTime >= 0)
	{
		if (!musicAudio.IsPlaying())
			musicAudio.Play();
		else
			musicTime = musicPos;
	}
	else
	{
		musicTime += deltaTime;
	}

	for (auto& noteObject : noteObjects)
	{
		noteObject.lastDiffTime = abs(noteObject.time - musicTime);
		noteObject.Update(deltaTime);
	}

	if (noteIndex < notes.size())
	{
		if (GetMusicTime() > notes[noteIndex].time)
		{
			while (notes[noteIndex].time <= GetMusicTime())
			{
				noteObjects.push_back(Note(notes[noteIndex].type, notes[noteIndex].line, notes[noteIndex].time, offset));
				noteIndex++;
				if (noteIndex >= notes.size())
					break;
			}
		}
	}

	for (int i = 0; i < noteObjects.size(); i++)
	{
		if (noteObjects[i].IsDead)
		{
			ShowEffect(5, noteObjects[i].line);
			ComboBreak();
			judgeStore[5]++;
			noteObjects.erase(noteObjects.begin() + i);
		}
	}

	for (int i = 0; i < effects.size(); i++)
	{
		effects[i].Update(deltaTime);
		if (effects[i].IsEnded)
		{
			effects.erase(effects.begin() + i);
		}
	}

#pragma region Input
	if (GetAsyncKeyState('Z') < 0) // Z 키
	{
		if (keys[0] == KeyState::FREE) // TODO 인풋 제작
		{
			keys[0] = KeyState::Stay;
			CheckLine(0);
		}
	}
	else
	{
		keys[0] = KeyState::FREE;
	}

	if (GetAsyncKeyState('X') & 0x8000) // X 키
	{
		if (keys[1] == KeyState::FREE) // TODO 인풋 제작
		{
			keys[1] = KeyState::Stay;
			CheckLine(1);
		}
	}
	else
	{
		keys[1] = KeyState::FREE;
	}

	if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) // . 키
	{
		if (keys[2] == KeyState::FREE) // TODO 인풋 제작
		{
			keys[2] = KeyState::Stay;
			CheckLine(2);
		}
	}
	else
	{
		keys[2] = KeyState::FREE;
	}

	if (GetAsyncKeyState(VK_OEM_2) & 0x8000) // / 키
	{
		if (keys[3] == KeyState::FREE) // TODO 인풋 제작
		{
			keys[3] = KeyState::Stay;
			CheckLine(3);
		}
	}
	else
	{
		keys[3] = KeyState::FREE;
	}
#pragma endregion
}

string getSpace(int count)
{
	string str = "";
	for (int i = 0; i < count; i++)
	{
		str += " ";
	}
	return str;
}

void GameScene::Render()
{
	if (IsEnded) return;
	/*Console::SetCursorPosition({ 2, 1 });
	cout << "FPS: " << fps << "           \n  ";
	cout << "Effects: " << effects.size() << "           ";*/

	Console::SetCursorPosition({ 100, 22 });
	cout << "Score: " << score;
	Console::SetCursorPosition({ 100, 24 });
	cout << "Combo: " << combo << "       ";
	Console::SetCursorPosition({ 100, 26 });
	cout << "MaxCombo: " << maxCombo;

	Console::SetCursorPosition({ 100, 30 });
	Console::SetBackgroundColor({ 255, 255, 255 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Marv: " << judgeStore[0];
	Console::SetCursorPosition({ 100, 32 });
	Console::SetBackgroundColor({ 245, 197, 66 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Perf: " << judgeStore[1];
	Console::SetCursorPosition({ 100, 34 });
	Console::SetBackgroundColor({ 7, 199, 0 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Great: " << judgeStore[2];
	Console::SetCursorPosition({ 100, 36 });
	Console::SetBackgroundColor({ 0, 69, 173 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Good: " << judgeStore[3];
	Console::SetCursorPosition({ 100, 38 });
	Console::SetBackgroundColor({ 74, 74, 74 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Okay: " << judgeStore[4];
	Console::SetCursorPosition({ 100, 40 });
	Console::SetBackgroundColor({ 189, 0, 0 });
	cout << "  ";
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);
	cout << " Miss: " << judgeStore[5];

	for (auto effect : effects)
	{
		effect.Render();
	}

	for (int i = 0; i < 4; i++)
	{
		bool isRendered = false;
		for (auto effect : effects)
		{
			if (effect.line == i)
			{
				isRendered = true;
				break;
			}
		}

		if (isRendered) continue;

		Console::SetCursorPosition({ 20 + 15 * i, judgePos });
		if (keys[i] == KeyState::Stay)
		{
			Console::SetBackgroundColor({ 102, 107, 115 });
		}
		else
		{
			Console::SetBackgroundColor(Color::DefaultForgroundColor);
		}
		cout << str;
	}
	Console::SetBackgroundColor(Color::DefaultBackgroundColor);

	Color color;
	if (combo < 10)
		color = Color::DefaultForgroundColor;
	else if (combo < 50)
		color = { 255, 255, 100 };
	else if (combo < 100)
		color = { 100, 255, 255 };
	else
		color = { 255, 100, 255 };

	for (int i = noteObjects.size() - 1; i >= 0; i--)
	{
		noteObjects[i].Render(ColorGradiant(life));
		//if (noteObject.lastDiffTime < 18)
		//	noteObject.Render({ 255, 0, 0 });
		//else 
		//	noteObject.Render(lineColor[noteObject.line]);
	}
}

void GameScene::AddLife(int life)
{
	this->life += life;
	if (this->life > 100)
		this->life = 100;
}

void GameScene::ShowEffect(int type, int line)
{
	Color color;
	switch (type)
	{
	case 0:
		color = { 255, 255, 255 };
		break;
	case 1:
		color = { 245, 197, 66 };
		break;
	case 2:
		color = { 7, 199, 0 };
		break;
	case 3:
		color = { 0, 69, 173 };
		break;
	case 4:
		color = { 74, 74, 74 };
		break;
	case 5:
		color = { 189, 0, 0 };
		break;
	default:
		break;
	}

	for (int i = 0; i < effects.size(); i++)
	{
		if (effects[i].line == line)
		{
			effects[i].time = 0;
		}
	}

	Effect effect(color, Color::DefaultForgroundColor, line, 500);
	effects.push_back(effect);
}
