#include "TitleScene.h"
#include "Global.h"

Generator<int> fadeText(string text, int duration, int posY = 6)
{
    duration /= 10;
    Color color = Color::DefaultBackgroundColor;
    for (int i = 0; i < duration; i++)
    {
        Console::SetCursorPosition({ 0, posY });
        Console::SetTextColor(color.Lerp(Color::DefaultForgroundColor, (float)i / duration));
        Console::AlignedPrint(TextAlign::Center, text.c_str());
        co_yield 1;
    }
    co_yield duration * 10;
    for (int i = duration; i > 0; i--)
    {
        Console::SetCursorPosition({ 0, posY });
        Console::SetTextColor(color.Lerp(Color::DefaultForgroundColor, (float)i / duration));
        Console::AlignedPrint(TextAlign::Center, text.c_str());
        co_yield 1;
    }
    co_yield -1;
}

Generator<int> fadeText(wstring text, int duration, int posY = 6)
{
    duration /= 10;
    Color color = Color::DefaultBackgroundColor;
    for (int i = 0; i < duration; i++)
    {
        Console::SetCursorPosition({ 0, posY });
        Console::SetTextColor(color.Lerp(Color::DefaultForgroundColor, (float)i / duration));
        Console::AlignedPrint(TextAlign::Center, text.c_str());
        co_yield 1;
    }
    co_yield duration * 10;
    for (int i = duration; i > 0; i--)
    {
        Console::SetCursorPosition({ 0, posY });
        Console::SetTextColor(color.Lerp(Color::DefaultForgroundColor, (float)i / duration));
        Console::AlignedPrint(TextAlign::Center, text.c_str());
        co_yield 1;
    }
    co_yield -1;
}

Generator<int> HelpText()
{
    return fadeText("이 게임은 1920 x 1080 의 해상도에서 플래이하지 않을 시 글자가 깨져보일 수 있습니다.", 3000);
}

Generator<int> LoadingText()
{
    int count = 0;
    wstring text = L"⢿⣻⣽⣾⣷⣯⣟⡿";

    while (true)
    {
        Console::SetUTF8(true);
        Console::SetCursorPosition({ 2, Console::GetScale().y - 2 });
        Console::SetTextColor(Color::DefaultForgroundColor);
        wcout << text[count++ % text.size()] << L" Loading...";
        Console::SetUTF8(false);
        co_yield 100;
    }
}

void Help()
{
    auto task1 = HelpText();
    auto task2 = LoadingText();

    Time time;
    time.Reset();
    while (true)
    {
        if (task1() == -1) break;
        if (task2() == -1) break;
        while (clock() - time.GetStartTime() < 1);
        task1.delay -= clock() - time.GetStartTime();
        task2.delay -= clock() - time.GetStartTime();
        time.Reset();
    }
}

void Title()
{
    auto task1 = LoadingText();
    auto task2 = fadeText(L"아무키나 누르면 게임이 시작됩니다.", 3000);

    Time time;
    time.Reset();
    while (true)
    {
        if (task1() == -1) break;
        if (task2() == -1) break;
        while (clock() - time.GetStartTime() < 1);
        task1.delay -= clock() - time.GetStartTime();
        task2.delay -= clock() - time.GetStartTime();
        time.Reset();
    }
}

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
