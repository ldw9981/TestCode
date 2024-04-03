#include <Windows.h>
#include "mykeyboard.h"


#define KEYBOARD_MAX 256		// 전체 가상 키의 수


BYTE g_byKeyPrev[KEYBOARD_MAX];		// 이전 키의 정보
BYTE g_byKeyCurr[KEYBOARD_MAX];		// 현재 키의 정보
		
BYTE g_byKeyTurnDn[KEYBOARD_MAX];	// Down된 키의 정보
BYTE g_byKeyTurnUp[KEYBOARD_MAX];   // Up 된 키의 정보

BOOL   g_bInvalidMousePoint;
POINTS g_ptMouse;
BOOL   g_bLButtonUp;
BOOL   g_bLButtonDown;
BOOL   g_bRButtonUp;
BOOL   g_bRButtonDown;

void __MyKbdUpdate()
{
	int i = 0;
	bool ret = GetKeyboardState((PBYTE)&g_byKeyCurr);

	auto error = GetLastError();
	for (i = 0; i < KEYBOARD_MAX; i++)
	{
		g_byKeyTurnUp[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyPrev[i];
		g_byKeyTurnDn[i] = (g_byKeyPrev[i] ^ g_byKeyCurr[i]) & g_byKeyCurr[i];
	}
	memcpy(&g_byKeyPrev, &g_byKeyCurr, KEYBOARD_MAX);


}


BOOL __MyKbdIsTurnDn(BYTE vk)
{
	if(g_byKeyTurnDn[vk]&0x80)
		return TRUE;
	
	return FALSE;
}

BOOL __MyKbdIsTurnUp(BYTE vk)
{
	if(g_byKeyTurnUp[vk]&0x80)
		return TRUE;

	return FALSE;

}

BOOL __MyKbdIsCurrDn(BYTE vk)
{
	if(g_byKeyCurr[vk]&0x80)
		return TRUE;

	return FALSE;
}

BOOL __MyKbdIsCurrUp(BYTE vk)
{
	if(g_byKeyCurr[vk]&0x80)
		return FALSE;

	return TRUE;

}