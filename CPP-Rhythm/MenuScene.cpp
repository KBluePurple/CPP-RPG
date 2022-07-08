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
	int selected = 0;
	Console::Clear();

	while (true)
	{
		Console::SetCursorPosition({ 40, 10 });
		cout << "[↑] [↓] 로 이동, [Enter] 로 선택";

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
		case 224:
			switch (_getch())
			{
			case 72:
				if (selected > 0)
				{
					selected--;
				}
				break;
			case 80:
				if (selected < maps.size() - 1)
				{
					selected++;
				}
				break;
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
	Console::Clear();
	bool back = false;
	int selected = 0;

	while (!back)
	{
		Console::SetCursorPosition({ 40, 10 });
		cout << "[↑] [↓] 로 이동, [Enter] 로 선택, [ESC] 로 돌아가기";

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
		case 224:
			switch (_getch())
			{
			case 72:
				if (selected > 0)
				{
					selected--;
				}
				break;
			case 80:
				if (selected < map.difficulties.size() - 1)
				{
					selected++;
				}
				break;
			}
			break;
		case VK_RETURN:
			LoadScene(map.mp3File, map.difficulties[selected].mapFile, map, selected);
			Console::Clear();
			return;
			break;
		case VK_ESCAPE:
			back = true;
			break;
		}
	}
	Console::Clear();
}

	void MenuScene::LoadScene(wstring mp3File, string mapFile, Map map, int selected)
	{
		Console::Clear();
		string str = map.title + " - " + map.difficulties[selected].difficulty;;
		wstring wstr = wstring(str.begin(), str.end());
		GameScene* gameScene = new GameScene(wstr, mp3File, mapFile, speed);
		gameScene->Initialize();
		gameScene->Run();
		delete(gameScene);
	}

	void MenuScene::Render()
	{
	}
