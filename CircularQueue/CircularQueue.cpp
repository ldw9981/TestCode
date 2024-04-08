// CircularQueue.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <windows.h>
#include "mykeyboard.h"

using namespace std;
#define MAX_QUEUE_SIZE 30

#define MAX_KEY_COUNT 5
int g_CommandVKey[MAX_KEY_COUNT] = { VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN,VK_RETURN };
short g_KeyStatePrev[MAX_KEY_COUNT] = { 0,0,0,0,0 };
short g_KeyStateCurr[MAX_KEY_COUNT] = { 0,0,0,0,0 };
char g_CommandKeysChar[MAX_KEY_COUNT] = { 'L','R','U','D','E'};
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
	ULONGLONG inputTickCount=0;	
	Queue queue;	
	while (!g_Quit)
	{
		for (int i = 0; i < MAX_KEY_COUNT; i++)
		{	
			g_KeyStateCurr[i] = GetAsyncKeyState(g_CommandVKey[i]); //  0이면 눌리지 않은 상태, 0이 아니면 눌린 상태
			//키가 눌렸을때만 큐에 넣는다.
			if (g_KeyStatePrev[i] == 0 && g_KeyStateCurr[i] != g_KeyStatePrev[i])
			{
				inputTickCount = GetTickCount64();	// 마지막 입력시간을 기록한다.
				if (!queue.IsFull())
				{
					queue.Enqueue(g_CommandKeysChar[i]);
				}
				else
				{
					queue.Dequeue();
					queue.Enqueue(g_CommandKeysChar[i]);
				}				
				//Todo:  기술의 커맨드 목록과 일치하는게 있는지 확인하고 해당 기술의 이름을 출력한다. 
				
			}
			g_KeyStatePrev[i] = g_KeyStateCurr[i];
		}		
		// 마지막 입력후 300ms 지나면 큐를 전체 초기화한다.
		if (inputTickCount!=0 &&  GetTickCount64() - inputTickCount > 300)
		{	
			inputTickCount =  0;		
			while (!queue.IsEmpty())
				queue.Dequeue();
		}
	}	
	return 0;
}
