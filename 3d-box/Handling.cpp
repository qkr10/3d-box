#include "declarations.h"

static bool paint_trigger = false, lbutton = false, camera_rotate = false;
static bool is_paused = true, is_gravity = true;
/* trigger 변수 */

void handling_WM_CREATE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	setting();

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
	HPEN whiteP, redP, oldP;
	whiteP = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	redP = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	oldP = (HPEN)SelectObject(hdc, whiteP);
	//물체를 렌더링
	for (int n = 0; n < cubes_num(); n++) {
		set_paint_n(n);
		if (n == get_num()) SelectObject(hdc, redP);
		//6개의 면을 렌더링
		for (int i = 0; i < 6; i++) {
			//은면제거
			if (is_hidden(i)) continue;

			VV dots;
			for (int j = 0; j < 4; j++)
				dots.push_back(get_point(i, j));

			VP dot;
			vvtovp(dots, dot);
			for (int j = 0; j < 4; j++) {
				int jj = j + 1 == 4 ? 0 : j + 1;
				//점을 25개씩 찍는다
				COLORREF C = RGB(255, 255, 255);
				for (int i = -2; i < 3; i++)
					for (int k = -2; k < 3; k++)
						SetPixel(hdc, (int)dot[j].x + i, (int)dot[j].y + k, C);

				MoveToEx(hdc, (int)dot[j].x, (int)dot[j].y, NULL);
				LineTo(hdc, (int)dot[jj].x, (int)dot[jj].y);
			}

			VV lines; VP line;
			get_line(dots, lines);
			vvtovp(lines, line);
			int k = 0;
			while (k < line.size())
			{
				MoveToEx(hdc, (int)line[k].x, (int)line[k].y, NULL); k++;
				LineTo(hdc, (int)line[k].x, (int)line[k].y); k++;
			}
		}
		if (n == get_num()) SelectObject(hdc, whiteP);
	}
	SelectObject(hdc, oldP);

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

void handling_WM_SIZE(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT R;
	GetClientRect(hWnd, &R);
	set_display(R);
	paint_trigger = true;
	return;
}

void handling_WM_DESTROY(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LOG_destroy();
	FOV_destroy();
	LINE_destroy();
	KillTimer(hWnd, 0);
	KillTimer(hWnd, 1);
	KillTimer(hWnd, 2);
	KillTimer(hWnd, 3);
	KillTimer(hWnd, 4);
	PostQuitMessage(0);
	ExitProcess(0);
	return;
}

void handling_WM_HSCROLL(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch ((int)GetMenu((HWND)lParam))
	{
	case FOV_id:
		FOV_handling(wParam, lParam);
		break;
	case LINE_id:
		LINE_handling(wParam, lParam);
		break;
	}
	return;
}
/************************/
/*                      */
/* 메세지 핸들링 함수들 */
/*                      */
/************************/

void Box_Translation(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	static const XMVECTOR Up = XMVectorSet(0, 100, 0, 0);

	static bool TT[2] = { false, false };
	if (!(_key('U') || _key('J'))) {
		TT[0] = TT[1] = false;
		goto EXCEPTION;
	}
	XMVECTOR V = XMVectorZero();
	if (_key('U')) {
		V = Up;
		if (!TT[0])
			LOG_print(TEXT("\r\n상승(U)"));
		TT[0] = true;
	}
	else TT[0] = false;
	if (_key('J')) {
		V = -1 * Up;
		if (!TT[1])
			LOG_print(TEXT("\r\n하강(J)"));
		TT[1] = true;
	}
	else TT[1] = false;

	if (!is_bumped(V))
		goto EXCEPTION;
	paint_trigger = true;
EXCEPTION:

	static bool T[4] = { false, false, false, false };
	if (!(_key(VK_UP) || _key(VK_DOWN) || _key(VK_LEFT) || _key(VK_RIGHT))) {
		T[0] = T[1] = T[2] = T[3] = false;
		goto EXCEPTION1;
	}
	XMVECTOR Axis = XMVectorSet(1, 0, 0, 0);
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
	static bool T[4] = { false, false, false, false };
	if (!(_key('W') || _key('A') || _key('D') || _key('S'))) {
		T[0] = T[1] = T[2] = T[3] = false;
		return;
	}
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
	if (!(paint_trigger || FOV_paint() || LINE_paint()))
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
	if (_key1('N')) {
		create_new();
		paint_trigger = true;
		LOG_print(TEXT("\r\n새 물체 생성(n)"));
	}
	if (_key1(VK_TAB)) {
		set_num(get_num() + 1);
		paint_trigger = true;
		LOG_print(TEXT("\r\n다른 물체 선택(tab)"));
	}
	return;
}
/************************/
/*                      */
/* 타이머 핸들링 함수들 */
/*                      */
/************************/