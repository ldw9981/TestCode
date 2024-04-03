#ifndef __MYKEYBOARD_H__
#define __MYKEYBOARD_H__
/************************************************************************/
/*
	Ű���忡 ���� ���
	__MyKbdUpdate()�� ���� �������� ȣ���ϸ� Ű�� ���¸�
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// ���� Ű�� ����
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// ���� Ű�� ����

	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down�� Ű�� ����
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up �� Ű�� ����
	�� �־� �����Ѵ�.
	
	IsCurr,IsTurn���� �Լ��� ����Ͽ� �ʿ��Ҷ� �ش� Ű���¸� Ȯ���Ѵ�.
*/
/************************************************************************/

#include "windows.h"

extern BOOL   g_bInvalidMousePoint;
extern POINTS g_ptMouse;
extern BOOL   g_bLButtonUp;
extern BOOL   g_bLButtonDown;
extern BOOL   g_bRButtonUp;
extern BOOL   g_bRButtonDown;

void __MyKbdUpdate();

BOOL __MyKbdIsCurrDn(BYTE vk);
BOOL __MyKbdIsCurrDn(BYTE vk);


BOOL __MyKbdIsTurnDn(BYTE vk);


BOOL __MyKbdIsTurnUp(BYTE vk);

BOOL __MyKbdIsCurrDn(BYTE vk);

BOOL __MyKbdIsCurrUp(BYTE vk);

#endif//__MYKEYBOARD_H__