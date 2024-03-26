// ConsoleDoubleBuffering.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "ConsoleRenderer.h"

#define ARROW_UP	0x48
#define ARROW_LEFT	0x4b
#define ARROW_RIGHT	0x4d
#define ARROW_DOWN	0x50
#define KEY_SPACE	0x20

bool g_bQuit = false;
void Update();
void Render();
void ProcessInput();

COORD g_Player = { 0,0 };

int main()
{
	ConsoleRenderer::ScreenInit();

	while (!g_bQuit)
	{
		ProcessInput();
		Update();
		Render();
	};

	ConsoleRenderer::ScreenRelease();
}


void ProcessInput()
{
	if(!_kbhit())
		return;

	char key = (char)_getch();
	switch (key)
	{
	case ARROW_LEFT:
		g_Player.X--;
		break;
	case ARROW_RIGHT:
		g_Player.X++;
		break;
	case ARROW_UP:
		g_Player.Y--;
		break;
	case ARROW_DOWN:
		g_Player.Y++;
		break;
	default:
		break;
	}
}

void Update()
{
	if (g_Player.X < 0) g_Player.X = 0;
	if (g_Player.X >= ConsoleRenderer::ScreenWidth()) g_Player.X = ConsoleRenderer::ScreenWidth() - 1;
	if (g_Player.Y < 0) g_Player.Y = 0;
	if (g_Player.Y >= ConsoleRenderer::ScreenHeight()) g_Player.Y = ConsoleRenderer::ScreenHeight() - 1;
}

void Render()
{
	ConsoleRenderer::ScreenClear();
	ConsoleRenderer::ScreenSetString(0, 0, "Hello 안녕", FG_PINK_DARK);
	ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y, 'P', FG_WHITE);
	ConsoleRenderer::ScreenFlipping();
}


