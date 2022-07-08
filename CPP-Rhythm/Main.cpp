#include "GlobalStd.h"
#include "Main.h"
#include "Console.h"
#include "Game.h"

using namespace chrono;

void Initialize()
{
    Color::DefaultForgroundColor = Color(171, 178, 191);
    Color::DefaultBackgroundColor = Color(40, 44, 52);
    Console::Initialize();
}

int main()
{
    Initialize();

    Game game;
    game.Initialize();
    game.MainTask();
}