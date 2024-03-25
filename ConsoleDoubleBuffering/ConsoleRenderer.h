#pragma once
#include <Windows.h>

namespace ConsoleRenderer
{
	void ScreenInit();
	void ScreenRelease();

	void ScreenFlipping();
	void ScreenClear();	

    bool ScreenSetChar(int x, int y, char ch, WORD bg, WORD fg);
	bool ScreenSetChar2B(int x, int y, char ch[2], WORD bg, WORD fg);
	bool ScreenSetString(int x, int y, char* pStr, WORD bg, WORD fg);
	bool ScreenSetAttr(WORD bg, WORD fg);
};