#include "declarations.h"

static bool paint_trigger = false, lbutton = false, camera_rotate = false;
static bool is_paused = true, is_gravity = true;
/* trigger 변수 */

void handling_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
	setting();
	LOG_setting(hWnd, hInstance);
	FOV_setting(hWnd, hInstance);
	EDIT_setting(hWnd, hInstance);

	SetTimer(hWnd, 0, 1000 / 45, (TIMERPROC)Paint_Trigger); //초당45번출력
	SetTimer(hWnd, 1, 1000 / 50, (TIMERPROC)Box_Translation);
	SetTimer(hWnd, 2, 1000 / 50, (TIMERPROC)Physic_Effects);
	SetTimer(hWnd, 3, 1000 / 50, (TIMERPROC)Camera_Movement);
	SetTimer(hWnd, 4, 1000 / 50, (TIMERPROC)Key_Check);
	return;
}

void handling_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(hWnd, &ps);

	//더블버퍼링
	RECT client_size; GetClientRect(hWnd, &client_size);
	HDC hdc = CreateCompatibleDC(h_dc);
	HBITMAP mem_new = CreateCompatibleBitmap(h_dc, client_size.right, client_size.bottom);
	HBITMAP mem_old = (HBITMAP)SelectObject(hdc, mem_new);

	//하이얀 펜을 준비
	HPEN NewP, OldP;
	NewP = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	OldP = (HPEN)SelectObject(hdc, NewP);
	//6개의 면을 렌더링
	for (int i = 0; i < 6; i++) {
		//은면제거
		if (is_hidden(i)) continue;

		for (int j = 0; j < 4; j++) {
			POINT P1, P2;
			get_point(i, j, P1, P2);

			//점을 25개씩 찍는다
			COLORREF C = RGB(255, 255, 255);
			for (int i = -2; i < 3; i++)
				for (int j = -2; j < 3; j++)
					SetPixel(hdc, (int)P1.x + i, (int)P1.y + j, C);

			MoveToEx(hdc, (int)P1.x, (int)P1.y, NULL);
			LineTo(hdc, (int)P2.x, (int)P2.y);
		}
	}
	SelectObject(hdc, OldP);

	BitBlt(h_dc, 0, 0, client_size.right, client_size.bottom, hdc, 0, 0, SRCCOPY);
	mem_new = (HBITMAP)SelectObject(hdc, mem_old);

	DeleteObject(mem_new);
	DeleteDC(hdc);
	EndPaint(hWnd, &ps);
	return;
}

void handling_WM_MOUSEMOVE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		LOG_print(TEXT("\r\n(왼드래그)"));
	}
	else if (wParam & MK_RBUTTON)
	{
		if (!camera_rotate) {
			oldPx = Px; oldPy = Py;
			LOG_print(TEXT("\r\n(오른드래그)"));
		}
		FLOAT Angle_x = XMConvertToRadians((oldPx - Px) * (float)0.1);
		FLOAT Angle_y = XMConvertToRadians((oldPy - Py) * (float)0.1);
		oldPx = Px; oldPy = Py;

		camera_rotating(Angle_x, Angle_y);

		paint_trigger = true;
		camera_rotate = true;
	}
}

void handling_WM_LBUTTONUP(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	lbutton = false;
	paint_trigger = true;
	return;
}

void handling_WM_RBUTTONUP(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	camera_rotate = false;
	return;
}

void handling_WM_DESTROY(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LOG_destroy();
	FOV_destroy();
	EDIT_destroy();
	KillTimer(hWnd, 0);
	KillTimer(hWnd, 1);
	KillTimer(hWnd, 2);
	KillTimer(hWnd, 3);
	KillTimer(hWnd, 4);
	PostQuitMessage(0);
	ExitProcess(0);
	return;
}

void handling_WM_COMMAND(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	EDIT_setting(hWnd, wParam);
	return;
}
/* 메세지 핸들링 함수들 */

void Box_Translation(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static const XMVECTOR Up = XMVectorSet(0, 100, 0, 0);

	if (_key('U') || _key('J')) {
		XMVECTOR V = XMVectorZero();
		static bool T[2] = { false, false };
		if (_key('U')) {
			V = Up;
			if (!T[0])
				LOG_print(TEXT("\r\n상승(U)"));
			T[0] = true;
		}
		else T[0] = false;
		if (_key('J')) {
			V = -1 * Up;
			if (!T[1])
				LOG_print(TEXT("\r\n하강(J)"));
			T[1] = true;
		}
		else T[1] = false;

		if (!is_bumped(V))
			goto EXCEPTION;
		paint_trigger = true;
	}
EXCEPTION:

	if (_key(VK_UP) || _key(VK_DOWN) || _key(VK_LEFT) || _key(VK_RIGHT)) {
		XMVECTOR Axis = XMVectorSet(1, 0, 0, 0);
		static bool T[4] = { false, false, false, false };
		if (_key(VK_UP)) {
			if (!T[0])
				LOG_print(TEXT("\r\n회전(↑)"));
			T[0] = true;
		}
		else T[0] = false;
		if (_key(VK_DOWN)) {
			Axis = XMVectorSet(-1, 0, 0, 0);
			if (!T[1])
				LOG_print(TEXT("\r\n회전(↓)"));
			T[1] = true;
		}
		else T[1] = false;
		if (_key(VK_LEFT)) {
			Axis = XMVectorSet(0, -1, 0, 0);
			if (!T[2])
				LOG_print(TEXT("\r\n회전(←)"));
			T[2] = true;
		}
		else T[2] = false;
		if (_key(VK_RIGHT)) {
			Axis = XMVectorSet(0, 1, 0, 0);
			if (!T[3])
				LOG_print(TEXT("\r\n회전(→)"));
			T[3] = true;
		}
		else T[3] = false;

		if (!is_bumped(XMMatrixRotationAxis(Axis, XMConvertToRadians(1))))
			goto EXCEPTION1;
		paint_trigger = true;
	}
EXCEPTION1:

	return;
}

void Physic_Effects(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static bool T = false;
	if (!is_paused) {
		physic_calc(is_gravity);
		T = false;
		paint_trigger = true;
	}
	else {
		if (!T)
			physic_reset();
		T = true;
	}
	return;
}

void Camera_Movement(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (!(_key('W') || _key('A') || _key('D') || _key('S'))) return;
	static bool T[4] = { false, false, false, false };
	if (_key('W')) {
		if (!T[0])
			LOG_print(TEXT("\r\n전진(W)"));
		T[0] = true;
		front();
	}
	else T[0] = false;
	if (_key('A')) {
		if (!T[1])
			LOG_print(TEXT("\r\n왼쪽(A)"));
		T[1] = true;
		left();
	}
	else T[1] = false;
	if (_key('S')) {
		if (!T[2])
			LOG_print(TEXT("\r\n후진(S)"));
		T[2] = true;
		rear();
	}
	else T[2] = false;
	if (_key('D')) {
		if (!T[3])
			LOG_print(TEXT("\r\n오른쪽(D)"));
		T[3] = true;
		right();
	}
	else T[3] = false;
	update_matrix();
	paint_trigger = true;
	return;
}

void Paint_Trigger(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (!paint_trigger && !FOV_paint())
		return;
	InvalidateRect(hWnd, NULL, true);
	paint_trigger = false;
	return;
}

void Key_Check(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if (_key(VK_ESCAPE)) {
		LOG_print(TEXT("\r\n종료!(esc)"));
		DestroyWindow(hWnd);
	}
	if (_key1(VK_SPACE)) {
		is_paused = !is_paused;
		LOG_print(is_paused ? TEXT("\r\n일시정지( )") : TEXT("\r\n재생( )"));
	}
	if (_key1('G')) {
		is_gravity = !is_gravity;
		LOG_print(is_gravity ? TEXT("\r\n중력 켜짐(g)") : TEXT("\r\n중력 꺼짐(g)"));
	}
	return;
}
/* 타이머 핸들링 함수들 */