#include "declarations.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	LPCWSTR ClassName = TEXT("¸À³­¿À¸®");
	LPCWSTR Title = TEXT("¤±¤¤¤·¤©");

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowW(ClassName, Title, WS_CLIPCHILDREN | WS_BORDER | WS_MINIMIZEBOX, 0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);
	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = { 0 };
	while (GetMessage(&msg, hWnd, 0, 0) != 0) {
		if (EDIT_msg(msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		handling_WM_CREATE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_PAINT:
		handling_WM_PAINT(hWnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		handling_WM_MOUSEMOVE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		handling_WM_LBUTTONUP(hWnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		handling_WM_RBUTTONUP(hWnd, uMsg, wParam, lParam);
		break;
	case WM_DESTROY:
		handling_WM_DESTROY(hWnd, uMsg, wParam, lParam);
		break;
	case WM_COMMAND:
		handling_WM_COMMAND(hWnd, uMsg, wParam, lParam);
		break;
	case WM_HSCROLL:
		FOV_handling(wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}