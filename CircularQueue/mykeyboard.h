#ifndef __MYKEYBOARD_H__
#define __MYKEYBOARD_H__
/************************************************************************/
/*
	키보드에 관한 모듈
	__MyKbdUpdate()를 게임 루프에서 호출하면 키의 상태를
	BYTE g_byKeyPrev[KEYBOARD_MAX];		// 이전 키의 정보
	BYTE g_byKeyCurr[KEYBOARD_MAX];		// 현재 키의 정보

	BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down된 키의 정보
	BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up 된 키의 정보
	에 넣어 보관한다.
	
	IsCurr,IsTurn관련 함수를 사용하여 필요할때 해당 키상태를 확인한다.
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