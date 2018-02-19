#include "defines.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	LPCWSTR ClassName = TEXT("¸À³­¿À¸®");
	LPCWSTR Title = TEXT("¤±¤¤¤·¤©");

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_inst = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowW(ClassName, Title, WS_BORDER | WS_MINIMIZEBOX | CS_DBLCLKS, 0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);
	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
			Key_handling(hWnd, msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		handing_WM_CREATE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_PAINT:
		handing_WM_PAINT(hWnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		handing_WM_MOUSEMOVE(hWnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		lbutton = false;
		paint_trigger = true;
		break;
	case WM_RBUTTONUP:
		camera_rotate = false;
		break;
	case WM_DESTROY:
		QUIT(hWnd, uMsg, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void handing_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < 8; i++)
		CUBE.V[i] = XMLoadFloat3(&(original_CUBE.F[i]));

	SetTimer(hWnd, 0, 1000 / 45, (TIMERPROC)Paint_Trigger); //ÃÊ´ç45¹øÃâ·Â
	SetTimer(hWnd, 1, 1000 / 50, (TIMERPROC)Box_Translation);
	SetTimer(hWnd, 2, 1000 / 50, (TIMERPROC)Physic_Effects);
	SetTimer(hWnd, 3, 1000 / 50, (TIMERPROC)Camera_Movement);
	
	_beginthread(LOG_Main, 0, NULL);

	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
	return;
}

void handing_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(hWnd, &ps);

	//´õºí¹öÆÛ¸µ
	RECT client_size; GetClientRect(hWnd, &client_size);
	HDC hdc = CreateCompatibleDC(h_dc);
	HBITMAP mem_new = CreateCompatibleBitmap(h_dc, client_size.right, client_size.bottom);
	HBITMAP mem_old = (HBITMAP)SelectObject(hdc, mem_new);

	//ÇÏÀÌ¾á ÆæÀ» ÁØºñ
	HPEN NewP, OldP;
	NewP = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	OldP = (HPEN)SelectObject(hdc, NewP);
	//6°³ÀÇ ¸éÀ» ·»´õ¸µ
	for (int i = 0; i < 6; i++)	{
		//Àº¸éÁ¦°Å
		XMVECTOR
			v1 = XMVector3TransformCoord(CUBE.V[index[i][0]], Camera_M),
			v2 = XMVector3TransformCoord(CUBE.V[index[i][1]], Camera_M),
			v3 = XMVector3TransformCoord(CUBE.V[index[i][2]], Camera_M),
			v4 = XMVector3TransformCoord(CUBE.V[index[i][3]], Camera_M);
		XMVECTOR normal = XMVector3Cross(v1 - v2, v1 - v4);
		if (XMVectorGetX(XMVector3Dot(normal, (v1 * 3 / 2) - (v2 / 2))) > 0) continue;
		if (XMVectorGetZ(v1) < 0 || XMVectorGetZ(v2) < 0 || XMVectorGetZ(v3) < 0 || XMVectorGetZ(v4) < 0) continue;

		for (int j = 0; j < 4; j++)	{
			XMVECTOR
				v1 = XMVector3TransformCoord(CUBE.V[index[i][j]], Camera_M),
				v2 = XMVector3TransformCoord(CUBE.V[index[i][(j + 1) == 4 ? 0 : j + 1]], Camera_M);

			//2Â÷¿øÀ¸·Î Á¡À» ¿Å±è
			FLOAT
				X1 = (XMVectorGetX(v1) / XMVectorGetZ(v1) / tanf(FOV / 2)) * 1000 + 960,
				Y1 = (XMVectorGetY(v1) / XMVectorGetZ(v1) / tanf(FOV / 2)) * 1000 + 540,
				X2 = (XMVectorGetX(v2) / XMVectorGetZ(v2) / tanf(FOV / 2)) * 1000 + 960,
				Y2 = (XMVectorGetY(v2) / XMVectorGetZ(v2) / tanf(FOV / 2)) * 1000 + 540;

			//Á¡À» 25°³¾¿ Âï´Â´Ù
			COLORREF C = RGB(255, 255, 255);
			for (int i = -2; i < 3; i++)
				for (int j = -2; j < 3; j++)
					SetPixel(hdc, (int)X1 + i, (int)Y1 + j, C);

			MoveToEx(hdc, (int)X1, (int)Y1, NULL);
			LineTo(hdc, (int)X2, (int)Y2);
		}
	}
	/*
	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 10, 990, TEXT("Áß·Â(key G)"), wcslen(TEXT("Áß·Â(key G)")));
	TextOut(hdc, 10, 1010, TEXT("ÀÏ½ÃÁ¤Áö(space)"), wcslen(TEXT("ÀÏ½ÃÁ¤Áö(space)")));
	if (is_gravity)
		TextOut(hdc, 140, 990, TEXT(": ÄÑÁü"), wcslen(TEXT(": ÄÑÁü")));
	else
		TextOut(hdc, 140, 990, TEXT(": ²¨Áü"), wcslen(TEXT(": ²¨Áü")));
	if (is_paused)
		TextOut(hdc, 140, 1010, TEXT(": ÄÑÁü"), wcslen(TEXT(": ÄÑÁü")));
	else
		TextOut(hdc, 140, 1010, TEXT(": ²¨Áü"), wcslen(TEXT(": ²¨Áü")));
		*/

	SelectObject(hdc, OldP);

	BitBlt(h_dc, 0, 0, client_size.right, client_size.bottom, hdc, 0, 0, SRCCOPY);
	mem_new = (HBITMAP)SelectObject(hdc, mem_old);

	DeleteObject(mem_new);
	DeleteDC(hdc);
	EndPaint(hWnd, &ps);
	return;
}

void handing_WM_MOUSEMOVE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int Px = LOWORD(lParam), Py = HIWORD(lParam);
	static int oldPx, oldPy;
	if (wParam & MK_LBUTTON)
	{
		paint_trigger = true;
		if (lbutton) return;
		oldPx = Px;
		oldPy = Py;
		lbutton = true;
	}
	else if (wParam & MK_RBUTTON)
	{
		if (!camera_rotate) { oldPx = Px; oldPy = Py; }
		Angle_x = XMConvertToRadians((oldPx - Px) * DPI);
		Angle_y = XMConvertToRadians((oldPy - Py) * DPI);
		oldPx = Px; oldPy = Py;

		XMMATRIX M = XMMatrixRotationAxis(up, Angle_x);
		Camera_LookAt = XMVector3TransformCoord(Camera_LookAt, M);
		Camera_R = XMVector3Cross(Camera_LookAt, up);
		M = XMMatrixRotationAxis(Camera_R, Angle_y);
		Camera_LookAt = XMVector3TransformCoord(Camera_LookAt, M);
		
		Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt + Camera_V, up);
		paint_trigger = true;
		camera_rotate = true;
	}
}

void Box_Translation(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static const XMVECTOR Up = XMVectorSet(0, 100, 0, 0);
	XMMATRIX M = XMMatrixIdentity();

	if (_key('U'))
		M = XMMatrixTranslationFromVector(Up);
	if (_key('J'))
		M = XMMatrixTranslationFromVector(-1 * Up);
	if (_key(VK_UP) || _key(VK_DOWN) || _key(VK_LEFT) || _key(VK_RIGHT)) {
		XMVECTOR Axis = XMVectorSet(1, 0, 0, 0);
		if (_key(VK_DOWN))
			Axis = XMVectorSet(-1, 0, 0, 0);
		if (_key(VK_LEFT))
			Axis = XMVectorSet(0, -1, 0, 0);
		if (_key(VK_RIGHT))
			Axis = XMVectorSet(0, 1, 0, 0);
		M = XMMatrixRotationAxis(Axis, XMConvertToRadians(1));
		XMVECTOR Center = (CUBE.V[0] + CUBE.V[6]) / 2;
		for (int i = 0; i < 8; i++)
			CUBE.V[i] = XMVector3TransformCoord(CUBE.V[i] - Center, M) + Center;
		paint_trigger = true;
		return;
	}
	if (XMMatrixIsIdentity(M))
		return;

	XMVECTOR Center = (XMVector3TransformCoord(CUBE.V[0], M) + XMVector3TransformCoord(CUBE.V[6], M)) / 2;
	if (XMVectorGetY(Center) < -0.1)
		return;

	for (int i = 0; i < 8; i++)
		CUBE.V[i] = XMVector3TransformCoord(CUBE.V[i], M);
	paint_trigger = true;
	return;
}

void Physic_Effects(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static const XMVECTOR g = XMVectorSet(0, -98, 0, 0);
	if (!is_paused) {
		FLOAT T = dwTime / (float)1000;
		CUBE.Veloc += T * ( is_gravity ? g + CUBE.Accel : XMVectorZero() );
		XMMATRIX M = XMMatrixTranslationFromVector(CUBE.Veloc * T / (float)2);

		XMVECTOR Center = (XMVector3TransformCoord(CUBE.V[0], M) + XMVector3TransformCoord(CUBE.V[6], M)) / 2;
		if (XMVectorGetY(Center) < -0.1) { //¶¥¿¡ ºÎµúÈû
			XMVectorSetY(CUBE.Veloc, -1 * XMVectorGetY(CUBE.Veloc));
			return;
		}

		for (int i = 0; i < 8; i++)
			CUBE.V[i] = XMVector3TransformCoord(CUBE.V[i], M);
		paint_trigger = true;
	}
	return;
}

void Camera_Movement(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (!(_key('W') || _key('A') || _key('D') || _key('S'))) return;
	if (_key('W')) Camera_V += Camera_LookAt * SPEED;
	if (_key('A')) Camera_V += Camera_R * SPEED;
	if (_key('D')) Camera_V += Camera_R * -1 * SPEED;
	if (_key('S')) Camera_V += Camera_LookAt * -1 * SPEED;
	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt + Camera_V, up);
	paint_trigger = true;
	return;
}

void Paint_Trigger(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (!paint_trigger)
		return;
	InvalidateRect(hWnd, NULL, true);
	paint_trigger = false;
	return;
}

void Key_handling(HWND hWnd, MSG msg)
{
	if (_key(VK_ESCAPE))
		QUIT(hWnd, msg.message, msg.wParam, msg.lParam);
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001) == 0x8001)
		is_paused = !is_paused;
	if ((GetAsyncKeyState('G') & 0x8001) == 0x8001)
		is_gravity = !is_gravity;
	return;
}

void QUIT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hWnd, 0);
	KillTimer(hWnd, 1);
	KillTimer(hWnd, 2);
	PostQuitMessage(0);
	return;
}