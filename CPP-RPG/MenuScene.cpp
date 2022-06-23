#include "MenuScene.h"
#include "Console.h"
#include "GameScene.h"

void MenuScene::Initialize()
{
	ifstream json_dir("data\\maps.json");
	Json::CharReaderBuilder builder;
	builder["collectComments"] = false;

	Json::Value value;
	JSONCPP_STRING errs;

	int startTime = clock();

	if (parseFromStream(builder, json_dir, &value, &errs))
	{
		for (auto item : value["maps"])
		{
			Map map;
			map.title = item["title"].asString();
			string path = item["mp3File"].asString();
			map.mp3File.assign(path.begin(), path.end());

			for (auto diff : item["difficulties"])
			{
				Difficulty diffi;
				diffi.difficulty = diff["difficulty"].asString();
				diffi.mapFile = diff["mapFile"].asString();
				map.difficulties.push_back(diffi);
			}

			maps.push_back(map);
		}
	}
	else
	{
		cout << "Parse failed.: " << errs << endl;
	}
}

void MenuScene::Run()
{
	Sleep(1000);
	int selected = 0;

	while (true)
	{
		Console::SetCursorPosition({ 40, 10 });
		cout << "[W] [S] 로 이동, [Enter] 로 선택";

		for (int i = 0; i < maps.size(); i++)
		{
			Console::SetCursorPosition({ 40, 15 + i });
			if (i == selected)
			{
				Console::SetTextColor({ 0, 255, 0 });
			}
			cout << maps[i].title;
			Console::SetTextColor(Color::DefaultForgroundColor);
		}

		switch (_getch())
		{
		case 'w':
			selected--;
			if (selected < 0)
			{
				selected = maps.size() - 1;
			}
			break;
		case 's':
			selected++;
			if (selected >= maps.size())
			{
				selected = 0;
			}
			break;
		case VK_RETURN:
			DifficultySelect(maps[selected]);
		}
	}
}

void MenuScene::Update()
{

}

void MenuScene::DifficultySelect(Map map)
{
	bool back = false;
	int selected = 0;

	while (!back)
	{
		Console::SetCursorPosition({ 40, 10 });
		cout << "[W] [S] 로 이동, [Enter] 로 선택";

		for (int i = 0; i < map.difficulties.size(); i++)
		{
			Console::SetCursorPosition({ 40, 15 + i });
			if (i == selected)
			{
				Console::SetTextColor({ 0, 255, 0 });
			}
			cout << map.title << " - " << map.difficulties[i].difficulty;
			Console::SetTextColor(Color::DefaultForgroundColor);
		}

		switch (_getch())
		{
		case 'w':
			selected--;
			if (selected < 0)
			{
				selected = map.difficulties.size() - 1;
			}
			break;
		case 's':
			selected++;
			if (selected >= map.difficulties.size())
			{
				selected = 0;
			}
			break;
		case VK_RETURN:
			LoadScene(map.mp3File, map.difficulties[selected].mapFile, map, selected);
			Console::Clear();
			return;
			break;
		}
	}
}

	void MenuScene::LoadScene(wstring mp3File, string mapFile, Map map, int selected)
	{
		Console::Clear();
		string str = map.title + " - " + map.difficulties[selected].difficulty;;
		wstring wstr = wstring(str.begin(), str.end());
		GameScene gameScene = GameScene(wstr, mp3File, mapFile, speed);
		gameScene.Initialize();
		gameScene.Run();
	}

	void MenuScene::Render()
	{
	}
