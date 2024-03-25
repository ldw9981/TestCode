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
    int nScreenBufferIndex = 0; // �ܼ�â�� ����Ű�� �ε���
    HANDLE hScreenBuffer[2];
    CONSOLE_SCREEN_BUFFER_INFO Info;
    HANDLE hConsoleHandle;

    HANDLE GetScreenBufferHandle()
    {      
        return hScreenBuffer[nScreenBufferIndex];
    }

    void ScreenInit()
    {
        // ���� ȭ��ũ�⿡ �´� ȭ�� �ֽܼ�ũ������ 2���� �����.    
        hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        hScreenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
        hScreenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
                
        // �⺻ �ܼ�,������ �ֽܼ�ũ�� ��� Ŀ�� �Ⱥ��̰� ����
        CONSOLE_CURSOR_INFO cursorInfo = { 0, };
        cursorInfo.bVisible = FALSE; 
        cursorInfo.dwSize = 1; // Ŀ���� ũ�⸦ ���� (1~100 ���̸� ����)
        SetConsoleCursorInfo(hConsoleHandle, &cursorInfo);     
        SetConsoleCursorInfo(hScreenBuffer[0], &cursorInfo);   
        SetConsoleCursorInfo(hScreenBuffer[1], &cursorInfo);   

        //�⺻ �ܼ��� ȭ�� ũ�� ������ ��´�.
        GetConsoleScreenBufferInfo(hConsoleHandle, &Info);
    }

    void ScreenFlipping()
    {
        SetConsoleActiveScreenBuffer(GetScreenBufferHandle());
        nScreenBufferIndex++;
        nScreenBufferIndex = nScreenBufferIndex % 2;  // 0,1,0,1,0,1,0,1....
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
        COORD Cur = { (SHORT)x, (SHORT)y };
        char buffer[10];
        sprintf_s(buffer, "%c", c);

        SetConsoleCursorPosition(GetScreenBufferHandle(), Cur);
        WriteFile(GetScreenBufferHandle(), buffer, 1, &dw, NULL);
    }

    void ScreenDraw(int x, int y, const char* pStr)
    {
        DWORD dw;
        COORD Cur = { (SHORT) x,(SHORT)y };
        SetConsoleCursorPosition(GetScreenBufferHandle(), Cur);
        WriteFile(GetScreenBufferHandle(), pStr, strlen(pStr), &dw, NULL);
    }

    int ScreenWidth()
    {
        return Info.dwSize.X;
    }
    int ScreenHeight()
    {
        return Info.dwSize.Y;
    }
};



