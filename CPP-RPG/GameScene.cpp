#include "GameScene.h"
#include "GlobalStd.h"
#include "Console.h"

float fps = 0;

void GameScene::Initialize()
{
	ifstream json_dir("map.json");
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

	musicAudio.Open(L"anima.mp3");

	lineColor[0] = Color::DefaultForgroundColor;
	lineColor[1] = { 66, 135, 245 };
	lineColor[2] = { 66, 135, 245 };
	lineColor[3] = Color::DefaultForgroundColor;

	musicTime = -offset;

	for (int i = 0; i < 15; i++)
	{
		str += " ";
	}
}

void GameScene::Run()
{
	int prevTime = startTime;
	while (true)
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
	life -= 10;
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
				AddLife(1);
				score += 350;
				judgeStore[0]++;
			}
			else if (diffTime < 43) // perfect
			{
				AddLife(1);
				score += 300;
				judgeStore[1]++;
			}
			else if (diffTime < 76) // great
			{
				score += 100;
				judgeStore[2]++;
			}
			else if (diffTime < 106) // good
			{
				score += 50;
				judgeStore[3]++;
			}
			else if (diffTime < 127) // okay
			{
				score += 20;
				judgeStore[4]++;
			}
			else if (diffTime < 164) // miss
			{
				if (noteObject.time - musicTime < 0)
				{
					continue;
				}
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
	
	if (life <= 0)
	{
		// musicAudio.Stop();
	}

	if (musicTime >= 0)
	{
		if (!musicAudio.IsPlaying())
			musicAudio.Play();
		else
			musicTime = musicAudio.GetPosition();
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
			ComboBreak();
			judgeStore[5]++;
			noteObjects.erase(noteObjects.begin() + i);
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
	Console::SetCursorPosition({ 2, 1 });
	cout << "FPS: " << fps << "           ";
	
	Console::SetCursorPosition({ 100, 22 });
	cout << "Score: " << score;
	Console::SetCursorPosition({ 100, 24 });
	cout << "Combo: " << combo << "       ";
	Console::SetCursorPosition({ 100, 26 });
	cout << "MaxCombo: " << maxCombo;
	
	Console::SetCursorPosition({ 100, 30 });
	cout << "Marv: " << judgeStore[0];
	Console::SetCursorPosition({ 100, 32 });
	cout << "Perf: " << judgeStore[1];
	Console::SetCursorPosition({ 100, 34 });
	cout << "Great: " << judgeStore[2];
	Console::SetCursorPosition({ 100, 36 });
	cout << "Good: " << judgeStore[3];
	Console::SetCursorPosition({ 100, 38 });
	cout << "Okay: " << judgeStore[4];
	Console::SetCursorPosition({ 100, 40 });
	cout << "Miss: " << judgeStore[5];

	//for (int i = 30; i >= 0; i--)
	//{
	//	if (life / 3.3333 > i)
	//		Console::SetBackgroundColor({ 100, 100, 100 });
	//	else
	//		Console::SetBackgroundColor({ 50, 50, 50 });

	//	Console::SetCursorPosition({ 82, 15 + 30 - i });
	//	cout << "  ";
	//}
	//Console::SetBackgroundColor(Color::DefaultBackgroundColor);

	Console::SetCursorPosition({ 20, judgePos });
	for (int i = 0; i < 4; i++)
	{
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

	for (int i = noteObjects.size() - 1; i >= 0; i--)
	{
		noteObjects[i].Render(lineColor[noteObjects[i].line]);
		//if (noteObject.lastDiffTime < 18)
		//	noteObject.Render({ 255, 0, 0 });
		//else 
		//	noteObject.Render(lineColor[noteObject.line]);
	}
}

void GameScene::AddLife(int life)
{
	life += life;
	if (life > 100)
		life = 100;
}
