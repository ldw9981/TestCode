#include "ConsoleRenderer.h"
#include <stdio.h>


/*
    
    Windows 11 22H2������ �ܼ� â�� ȣ��Ʈ�ϴ� �� ���Ǵ� �⺻ ���� Windows �͹̳� ����Ǿ����ϴ�.
    * ��� �ܼ�â ���� �Լ��� �۵�����. 
    https://support.microsoft.com/ko-kr/windows/windows-11-%EB%8C%80%ED%95%9C-%EB%AA%85%EB%A0%B9-%ED%94%84%EB%A1%AC%ED%94%84%ED%8A%B8-%EB%B0%8F-windows-powershell-6453ce98-da91-476f-8651-5c14d5777c20
*/
namespace ConsoleRenderer
{
    HANDLE hConsoleHandle;      // �ʱ� ȭ�� �ܼ��� �ڵ�
    CONSOLE_SCREEN_BUFFER_INFO Info; // �ʱ� ȭ�� �ܼ��� ȭ�� ����
    int nScreenBufferIndex = 0; // �ܼ�â�� ����� ��ũ�������� �ε���
    HANDLE hScreenBuffer[2];

    HANDLE GetCurrentScreenBufferHandle()
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
        // ���� �ܼ��� ����� ��ũ�������� Handle�� �����Ͽ� ȭ�鿡 �����ش�.
        SetConsoleActiveScreenBuffer(GetCurrentScreenBufferHandle());
        // ������ ����� ��ũ�� ������ �ε����� �������� �غ��Ѵ�.
        nScreenBufferIndex++;
        nScreenBufferIndex = nScreenBufferIndex % 2;  // 0,1,0,1,0,1,0,1....
    }

    void ScreenClear()
    {
        COORD Coor = { 0, 0 };
        DWORD dw;
        FillConsoleOutputCharacter(GetCurrentScreenBufferHandle(), ' ', Info.dwSize.X * Info.dwSize.Y, Coor, &dw);
    }

    void ScreenRelease()
    {
        CloseHandle(hScreenBuffer[0]);
        CloseHandle(hScreenBuffer[1]);
    }
   
    


    /*
        FOREGROUND_BLUE	�ؽ�Ʈ ���� �Ķ����� ���Ե˴ϴ�.
        COMMON_LVB_LEADING_BYTE	���� ����Ʈ�Դϴ�.

        https://learn.microsoft.com/ko-kr/windows/console/console-screen-buffers#character-attributes
    */


    bool ScreenSetChar(int x, int y, char ch, WORD bg, WORD fg)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        bRval = FillConsoleOutputCharacter(GetCurrentScreenBufferHandle(), ch, 1, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputCharacter()\n");

        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), bg | fg, 1, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }

    bool ScreenSetChar2B(int x, int y, char ch[2], WORD bg, WORD fg)
    {
        COORD	cdPos;
        bool	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        bRval = SetConsoleCursorPosition(GetCurrentScreenBufferHandle(), cdPos);
        if (!bRval)
            return false;

        printf("%c%c", ch[0], ch[1]);

        cdPos.X = x;
        cdPos.Y = y;
        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), bg | fg, 2, cdPos, &dwCharsWritten);
        if (bRval == false)
            printf("Error, FillConsoleOutputAttribute()\n");

        return bRval;
    }

    bool ScreenSetString(int x, int y, char* pStr, WORD bg, WORD fg)
    {
        COORD	cdPos;
        BOOL	bRval = FALSE;
        DWORD	dwCharsWritten;
        cdPos.X = x;
        cdPos.Y = y;

        DWORD nNumberOfBytesToWrite = strlen(pStr);

        SetConsoleCursorPosition(GetCurrentScreenBufferHandle(), cdPos);
        WriteFile(GetCurrentScreenBufferHandle(), pStr, nNumberOfBytesToWrite, &dwCharsWritten, NULL);

        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), bg | fg, nNumberOfBytesToWrite, cdPos, &dwCharsWritten);
        if (bRval == false) printf("Error, FillConsoleOutputAttribute()\n");
        return bRval;
    }

    bool ScreenSetAttr( WORD bg, WORD fg)
    {
        COORD	cdPos;
        bool	bRval = FALSE;
        DWORD	dwCharsWritten;
        //	int x,y;	

        cdPos.X = 0;
        cdPos.Y = 0;
        bRval = FillConsoleOutputAttribute(GetCurrentScreenBufferHandle(), bg | fg, Info.dwSize.X * Info.dwSize.Y, cdPos, &dwCharsWritten);
        if (bRval == false)
        {
            printf("Error, FillConsoleOutputCharacter()\n");
            return bRval;
        }

        return bRval;
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



