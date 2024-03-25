#pragma once

#include <Windows.h>

namespace ConsoleRenderer
{
	void InitScreen();
	void ScreenRelease();

	void ScreenFlipping();
	void ScreenClear();

	void ScreenDraw(int x, int y, const char c);
	void ScreenDraw(int x, int y, const char* pStr);
};