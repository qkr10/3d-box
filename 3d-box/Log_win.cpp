#include "declarations.h"

static HWND LOG_hWnd;

void LOG_setting(HWND hWnd, HINSTANCE g_inst)
{
	LOG_hWnd = CreateWindow(WC_EDIT, TEXT("Log"), WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
		10, 900, 200, 130, hWnd, (HMENU)50, g_inst, NULL);
	_beginthread(LOG_initialize, 0, NULL);
	return;
}

void LOG_initialize(void* param)
{
	Sleep(1); LOG_print(TEXT(""));
	return;
}

void LOG_print(LPCTSTR string)
{
	static TCHAR LOG[500] = TEXT("Log");
	static int LOG_i = -1;
	if (wcslen(LOG) > 480)
		wcscpy_s(LOG, TEXT("LOGâ �ʱ�ȭ"));
	wcscat_s(LOG, string);
	SetWindowText(LOG_hWnd, LOG);
	Edit_Scroll(LOG_hWnd, LOG_i++, 0);
	return;
}

void LOG_print(int i)
{
	TCHAR T[10];
	wsprintf(T, TEXT("\r\n%d"), i);
	LOG_print(T);
	return;
}

void LOG_print(float i)
{
	TCHAR T[20];
	swprintf_s(T, TEXT("\r\n%f"), i);
	LOG_print(T);
	return;
}

void LOG_destroy(void)
{
	DestroyWindow(LOG_hWnd);
	return;
}