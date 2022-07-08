#include "TitleScene.h"
#include "GlobalStd.h"
#include "Console.h"
#include "Time.h"

void TitleScene::Initialize()
{

}

void TitleScene::Run()
{
    Console::SetCursorPosition({ 0, 22 });
    Console::AlignedPrint(TextAlign::Center, L"  ██████╗██████╗ ██████╗       ██████╗ ██████╗  ██████╗ \n");
    Console::AlignedPrint(TextAlign::Center, L" ██╔════╝██╔══██╗██╔══██╗      ██╔══██╗██╔══██╗██╔════╝ \n");
    Console::AlignedPrint(TextAlign::Center, L" ██║     ██████╔╝██████╔╝█████╗██████╔╝██████╔╝██║  ███╗\n");
    Console::AlignedPrint(TextAlign::Center, L" ██║     ██╔═══╝ ██╔═══╝ ╚════╝██╔══██╗██╔═══╝ ██║   ██║\n");
    Console::AlignedPrint(TextAlign::Center, L" ╚██████╗██║     ██║           ██║  ██║██║     ╚██████╔╝\n");
    Console::AlignedPrint(TextAlign::Center, L"  ╚═════╝╚═╝     ╚═╝           ╚═╝  ╚═╝╚═╝      ╚═════╝ \n");
    Console::SetCursorPosition({ 0, 32 });
    Console::AlignedPrint(TextAlign::Center, "[ 아무키나 누르면 게임이 시작됩니다 ]");
    Console::Pause();
}

void TitleScene::Update()
{
}

void TitleScene::Render()
{
}
