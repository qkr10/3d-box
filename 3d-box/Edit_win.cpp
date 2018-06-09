#include "declarations.h"

static HWND EDIT_hWnd;

void EDIT_setting(HWND hWnd, WPARAM wParam)
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	if (LOWORD(wParam) == 53 && !IsWindow(EDIT_hWnd)) {
		EDIT_hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, EDIT_proc);
		if (EDIT_hWnd == NULL) LOG_print(TEXT("\r\n대화상자 오류"));
		ShowWindow(EDIT_hWnd, SW_SHOW);
	}
	return;
}

void EDIT_setting(HWND hWnd, HINSTANCE hInst)
{
	CreateWindow(TEXT("button"), TEXT("물체 편집"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 10, 80, 20, hWnd, (HMENU)53, hInst, NULL);
}

bool EDIT_msg(MSG &msg)
{
	return !IsDialogMessage(EDIT_hWnd, &msg) || !IsWindow(EDIT_hWnd);
}

LRESULT CALLBACK EDIT_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return true;
	case WM_COMMAND:
		switch (wParam) {
		case IDCLOSE:
			EDIT_destroy();
			break;
		}
	}
	return false;
}

void EDIT_destroy()
{
	DestroyWindow(EDIT_hWnd);
	return;
}