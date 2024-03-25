#include "ConsoleRenderer.h"
#include <stdio.h>
#include <Windows.h>

/*
    
    Windows 11 22H2������ �ܼ� â�� ȣ��Ʈ�ϴ� �� ���Ǵ� �⺻ ���� Windows �͹̳� ����Ǿ����ϴ�.
    * ��� �ܼ�â ���� �Լ��� �۵�����. 
    https://support.microsoft.com/ko-kr/windows/windows-11-%EB%8C%80%ED%95%9C-%EB%AA%85%EB%A0%B9-%ED%94%84%EB%A1%AC%ED%94%84%ED%8A%B8-%EB%B0%8F-windows-powershell-6453ce98-da91-476f-8651-5c14d5777c20
*/
namespace ConsoleRenderer
{
    bool bScreenBufferIndex = false; // 0
    HANDLE hScreenBuffer[2];
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hConsoleHandle;

    HANDLE GetScreenBufferHandle()
    {
        int index = (bScreenBufferIndex ? 1 : 0);
        return hScreenBuffer[index];
    }

    void GotoXY(int x, int y)
    {
        COORD Cur = { x, y };

        SetConsoleCursorPosition(hConsoleHandle, Cur);
    }

    void ScreenInit()
    {
        // ȭ�� ���� 2���� �����.
        bool bRval;
        hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        hScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        hScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        
        
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.bVisible = FALSE; // Ŀ���� ������ ���� ����(0�̸� �Ⱥ���, 0���� ���� ���̸� ����)
        cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
        bRval = SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);
        if (bRval == FALSE)
            printf("Error, SetConsoleCursorInfo()\n");

        GetConsoleScreenBufferInfo(hConsoleHandle, &Info);
    }

    void ScreenFlipping()
    {
        SetConsoleActiveScreenBuffer(GetScreenBufferHandle());
        bScreenBufferIndex = !bScreenBufferIndex;  // 0->1 , 1->0
    }

    void ScreenClear()
    {
        COORD Coor = { 0, 0 };
        DWORD dw;
        FillConsoleOutputCharacter(GetScreenBufferHandle(), ' ', Info.dwSize.X * Info.dwSize.Y, Coor, &dw);
    }

    void ScreenRelease()
    {
        CloseHandle(hScreenBuffer[0]);
        CloseHandle(hScreenBuffer[1]);
    }
   
    void ScreenDraw(int x, int y, const char c)
    {
        DWORD dw;
        COORD Cur = { x, y };
        char buffer[10];
        sprintf_s(buffer, "%c", c);

        SetConsoleCursorPosition(GetScreenBufferHandle(), Cur);
        WriteFile(GetScreenBufferHandle(), buffer, 1, &dw, NULL);
    }

    void ScreenDraw(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { x, y };
        SetConsoleCursorPosition(GetScreenBufferHandle(), Cur);
        WriteFile(GetScreenBufferHandle(), pStr, strlen(pStr), &dw, NULL);
    }
};



