#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"

void Game::Initialize()
{
	
}

void Game::MainTask()
{
    TitleScene titleScene;
	titleScene.Initialize();
	titleScene.Run();
	Console::Clear();

	GameScene gameScene;
	gameScene.Initialize();
	gameScene.Run();
}
