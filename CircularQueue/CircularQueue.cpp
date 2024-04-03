// CircularQueue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>
#include "mykeyboard.h"

using namespace std;
#define MAX_QUEUE_SIZE 30

#define MAX_COMMAND_COUNT 5
int g_CommandKeys[MAX_COMMAND_COUNT] = { VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN,VK_RETURN };
short g_CommandKeysStatePrev[MAX_COMMAND_COUNT] = { 0,0,0,0,0 };
short g_CommandKeysStateCurr[MAX_COMMAND_COUNT] = { 0,0,0,0,0 };
char g_CommandKeysChar[MAX_COMMAND_COUNT] = { 'L','R','U','D','E' };

bool g_Quit = false;
struct Queue
{
	char buf[MAX_QUEUE_SIZE] = { 0 };		//저장소
	int qsize = MAX_QUEUE_SIZE;		//저장소 크기
	int front = 0;		// 꺼낼 인덱스 ( 가장 오래전에 보관한 자료가 있는 인덱스)
	int rear = 0;			// 보관할 인덱스 
	int count = 0;		// 보관 개수

	// 원형큐가 꽉차있는지 확인
	bool IsFull()
	{
		return count == qsize;	//보관 개수가 qsize와 같으면 꽉찬 상태
	}

	// 원형큐가 비어있는지 확인
	bool IsEmpty()
	{
		return count == 0;				//보관 개수가 0이면 비어있는 상태	
	}

	// 원형큐에 문자 삽입하기
	bool Enqueue(char data)
	{
		if (IsFull())
		{
			cout << "Queue is Full" << endl;
			return false;
		}

		buf[rear]=data;
		rear++;
		rear = rear % qsize;
		count++;						//보관 개수 증가
		return true;
	}

	char Front()
	{
		return buf[front];
	}

	// 원형큐에서 문자 꺼내기
	void Dequeue()
	{
		char data = 0;
		if (IsEmpty())
		{
			cout << "Queue is Empty" << endl;			
		}

		front++;
		front = front % qsize;
		count--;						//	보관 개수 감소
	}

	void PrintAll()
	{
		if(IsEmpty())
			return;

		int temp_front = front;
		while ( temp_front != rear)
		{
			char data = buf[temp_front];
			printf("%c\n", data);

			temp_front++;
			temp_front = temp_front % qsize;
		}

	}
};




int main()
{
	int i = 0;
	Queue queue;
	
	short result=0,prev=0;

		
	BYTE Curr[256];		// 현재 키의 정보		


	while (!g_Quit)
	{
		for (i = 0; i < MAX_COMMAND_COUNT; i++)
		{
			g_CommandKeysStateCurr[i] = GetAsyncKeyState(g_CommandKeys[i]);
			if (g_CommandKeysStatePrev[i] == 0 && g_CommandKeysStateCurr[i] != g_CommandKeysStatePrev[i])
			{
				if (g_CommandKeys[i] == VK_RETURN)
				{
					queue.PrintAll();
				}
				else
				{
					queue.Enqueue(g_CommandKeysChar[i] );
				}
			}
			g_CommandKeysStatePrev[i] = g_CommandKeysStateCurr[i];
		}
	}

	
	cout << endl;
	system("pause");
	return 0;
}
