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
void ProcessInput(char key);

COORD g_Player = {0,0};

int main()
{
   ConsoleRenderer::ScreenInit();
      
   while (!g_bQuit)
   {
	   if (_kbhit())
	   {
		   ProcessInput((char)_getch());
	   }
	   Update();
	   Render();
   };

   ConsoleRenderer::ScreenRelease();
}


void ProcessInput(char key)
{
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

}

void Render()
{
	char test[]="dsdsdsd";
	ConsoleRenderer::ScreenClear();
	ConsoleRenderer::ScreenSetChar(g_Player.X, g_Player.Y+10,'1',10,10);
	ConsoleRenderer::ScreenSetString(g_Player.X, g_Player.Y, test, 10, 10);
	ConsoleRenderer::ScreenFlipping();
}


