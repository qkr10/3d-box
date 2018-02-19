#include "defines.h"

void __cdecl LOG_Main(void *p)
{
	LPCWSTR ClassName = TEXT("LOG");
	LPCWSTR Title = TEXT("LOG");

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = LOG_Proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_inst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowW(ClassName, Title, 0, 0, 950, 1920, 130, NULL, NULL, g_inst, NULL);
	if (!hWnd) return;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return;
}

LRESULT CALLBACK LOG_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		LOG_WM_CREATE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_PAINT:
		LOG_WM_PAINT(hWnd, uMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		LOG_QUIT(hWnd, uMsg, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void LOG_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	SetTimer(hWnd, 10, 1000 / 50, (TIMERPROC)Check_Trigger);
	return;
}

void LOG_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return;
}

void LOG_QUIT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hWnd, 10);
	PostQuitMessage(0);
	return;
}

void Check_Trigger(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static bool temp_g = is_gravity, temp_p = is_paused;
	if (temp_g != is_gravity || temp_p != is_paused) {
		temp_g = is_gravity;
		temp_p = is_paused;
		LOG_paint_trigger = true;
	}
	return;
}