#include "declarations.h"

static int LINE_NUM = 10;
static HWND LINE_hWnd, LINE_text_hWnd;
static bool paint_tri = false;

void LINE_setting(HWND hWnd, HINSTANCE hInst)
{
	LINE_text_hWnd = CreateWindow(TEXT("static"), TEXT("ºø±Ý¼ö Á¶Àý¡é"), WS_CHILD | WS_VISIBLE,
		220, 10, 90, 20, hWnd, (HMENU)LINE_text_id, hInst, NULL);
	LINE_hWnd = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
		220, 40, 200, 20, hWnd, (HMENU)LINE_id, hInst, NULL);
	SetScrollRange(LINE_hWnd, SB_CTL, 0, 50, false);
	SetScrollPos(LINE_hWnd, SB_CTL, 10, true);
	return;
}

int LINE_NUM_get()
{
	return LINE_NUM;
}

void LINE_destroy()
{
	DestroyWindow(LINE_hWnd);
	DestroyWindow(LINE_text_hWnd);
	return;
}

void LINE_handling(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(wParam))
	{
	case SB_LINELEFT:
		LINE_NUM = max(0, LINE_NUM - 1);
		break;
	case SB_LINERIGHT:
		LINE_NUM = min(1000, LINE_NUM + 1);
		break;
	case SB_PAGELEFT:
		LINE_NUM = max(0, LINE_NUM - 20);
		break;
	case SB_PAGERIGHT:
		LINE_NUM = min(1000, LINE_NUM + 20);
		break;
	case SB_THUMBTRACK:
		LINE_NUM = HIWORD(wParam);
		break;
	}
	SetScrollPos(LINE_hWnd, SB_CTL, (int)LINE_NUM, true);
	paint_tri = true;
	return;
}

bool LINE_paint()
{
	if (paint_tri) {
		paint_tri = false;
		return true;
	}
	return false; 
}