#include "Game.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "Console.h"

void Game::Initialize()
{
	
}

void Game::MainTask()
{
	while (true)
	{
		TitleScene titleScene = TitleScene();
		titleScene.Initialize();
		titleScene.Run();
		Console::Clear();

		while (true)
		{
			MenuScene menuScene = MenuScene();
			menuScene.Initialize();
			menuScene.Run();
			Console::Clear();
		}
	}
}
