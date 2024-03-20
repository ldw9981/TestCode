// CharCalculator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <stdlib.h>

#define LENGTH 10


char atoc(char c)
{
    if(c == '\0') 
        return 0; // null문자면 0을 반환
   
	return c - '0';
}
char ctoa(char c)
{
	return c + '0';
}

int main()
{
    char ArrayNum1[LENGTH] = { '1','4','3' };
    char ArrayNum2[LENGTH] = { '8','9','8' };
    char ArraySum[LENGTH] = { 0 };

    char test = atoc('\0');

    char remainder=0,quotient=0,sum=0;
    for (char i = 0; i < LENGTH - 1; i++)
    {
        sum = atoc(ArrayNum1[i]) + atoc(ArrayNum2[i]) + quotient; // 덧셈
        quotient = sum / 10;    // 몫
        remainder = sum % 10;   // 나머지
        ArraySum[i] = ctoa(remainder);  // 나머지를 배열에 저장
    }
}

