#include "declarations.h"

static FLOAT FOV = 90;
static bool paint_tri = false;
static HWND FOV_hWnd, FOV_hWnd1;

void FOV_setting(HWND hWnd, HINSTANCE hInst)
{
	FOV_hWnd1 = CreateWindow(TEXT("static"), TEXT("FOV Á¶Àý¡é"), WS_CHILD | WS_VISIBLE,
		10, 840, 80, 20, hWnd, (HMENU)102, hInst, NULL);
	FOV_hWnd = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
		10, 870, 200, 20, hWnd, (HMENU)101, hInst, NULL);
	SetScrollRange(FOV_hWnd, SB_CTL, 0, 1000, false);
	SetScrollPos(FOV_hWnd, SB_CTL, 500, true);
	return;
}

void FOV_handling(WPARAM wParam, LPARAM lParam)
{
	static int F;
	switch (LOWORD(wParam))
	{
	case SB_LINELEFT:
		F = max(0, F - 1);
		break;
	case SB_LINERIGHT:
		F = min(1000, F + 1);
		break;
	case SB_PAGELEFT:
		F = max(0, F - 20);
		break;
	case SB_PAGERIGHT:
		F = min(1000, F + 20);
		break;
	case SB_THUMBTRACK:
		F = HIWORD(wParam);
		break;
	}
	SetScrollPos(FOV_hWnd, SB_CTL, (int)F, true);
	FOV = (F - 500) / (float)1000 + 90;
	paint_tri = true;
	return;
}

float FOV_get()
{
	return FOV;
}

bool FOV_paint()
{
	if (paint_tri) {
		paint_tri = false;
		return true;
	}
	else
		return false;
}

void FOV_destroy()
{
	DestroyWindow(FOV_hWnd);
	DestroyWindow(FOV_hWnd1);
	return;
}