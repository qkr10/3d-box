/*
=                       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
=                     @@V[4]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
=                   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[5]@
=                 @@@@@@@@@@                                                           @@@@@@
=               @@@@@@ @@@@@                                                         @@@@@@@@
=             @@@@@@   @@@@@                                                       @@@@@ @@@@
=           @@@@@@     @@@@@                                                     @@@@@   @@@@
=         @@@@@@       @@@@@                                                   @@@@@     @@@@
=       @@@@@@         @@@@@                                                 @@@@@       @@@@
=     @@@@@@           @@@@@                                               @@@@@         @@@@
=   @@@@@@                                                               @@@@@           @@@@
= @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             @@@@
=V[0]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[1]               @@@@
=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@               @@@@
=@@@@                                                                 @@@@               @@@@
=@@@@                                                                 @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                                                                 @@@@               @@@@
=@@@@                                                                 @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@                                          @@@@               @@@@
=@@@@                  @@@@@    @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@   @@@@  @@@@@@@@@@@@@@@@@
=@@@@                  @V[7]    @@@@@@@@@@@@@@@    @@@@@@@@@@@@@@@@   @@@@  @@@@@@@@@@@@@V[6]
=@@@@                                                                 @@@@             @@@@@
=@@@@                                                                 @@@@           @@@@@
=@@@@          @@@@@                                                  @@@@         @@@@@
=@@@@        @@@@@                                                    @@@@       @@@@@
=@@@@      @@@@@                                                      @@@@     @@@@@
=@@@@    @@@@@                                                        @@@@   @@@@@
=@@@@  @@@@@                                                          @@@@ @@@@@
=@@@@@@@@                                                             @@@@@@@@
=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
=V[3]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[2]
���������� ������ x����
���� ������ y����
�ڷ� ������ z����
������ �𼭸��� ����2000


=      y��                                               ȭ��                                         :::::::
=     .+++.                                               %                                   :::::::
=   ++  %  ++                                             %                            :::::::
= ++    %    ++                                           %                     .::::::
=       %                                                 %              :::::::
=       %                                                 %       :::::::
=       %                                                 %:::::::
=       %                                           ::::::%
=       %                                    :::::::      %                  ::::
=       %                             :::::::             %                ::    :::::::::::
=       %                      :::::::                    %               ::                :::::::::::
=       %               :::::::                           %              ::                            ::::
= ::::::%:::::::::::::::                                  %            ::                                ::  +
= :     %        :                                        %           ::                                ::    +
= :    ����(ī�޶�)::::::::::::::::::::::::::::::::::::::::.%.:::::::::::::::::::::::::::::::::::::::::::::::::::z��
= ::::::::::::::::::                                      %         ::                                ::      +
=                   ::::::::                              %        ::                                ::      +
=                           ::::::::                      %       :::::                             ::
=                                   ::::::::              %            :::::::::::                 ::
=                                           ::::::::      %                       :::::::::::     ::
=                                                   ::::::%                                 :::::::
=                                                         %::::::::
=                                                         %        :::::::
=                                                         %               :::::::::
=                                                         %                        :::::::
=                                                         %                               ::::::::
=                                                         %                                       ::::::::
=                                                         %                                               :
�þ߰� : 16/9 ~ -16/9
*/

#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

const float DISTANCE = 500;

//�ո� �ð����	:0123
//�޸� �ð����	:5476
//���� �ð����	:3740
//������ �ð����	:1562
//���� �ð����	:4510
//�Ʒ��� �ð����	:7326
struct original_CUBE_struct
{
	XMFLOAT3 F[8] = {
		{ (FLOAT)-1000, (FLOAT)1000, (FLOAT)-1000 },
		{ (FLOAT)1000, (FLOAT)1000, (FLOAT)-1000 },
		{ (FLOAT)1000, (FLOAT)-1000, (FLOAT)-1000 },
		{ (FLOAT)-1000, (FLOAT)-1000, (FLOAT)-1000 },
		{ (FLOAT)-1000, (FLOAT)1000, (FLOAT)1000 },
		{ (FLOAT)1000, (FLOAT)1000, (FLOAT)1000 },
		{ (FLOAT)1000, (FLOAT)-1000, (FLOAT)1000 },
		{ (FLOAT)-1000, (FLOAT)-1000, (FLOAT)1000 } };
	//8���� ���� ��ǥ
}original_CUBE;

struct CUBE_struct
{
	XMVECTOR V[8] = { NULL, }; //��ü���θ� �������� ��������
}CUBE;

int index[6][4] = { { 0,1,2,3 },{ 5,4,7,6 },{ 3,7,4,0 },{ 1,5,6,2 },{ 4,5,1,0 },{ 7,3,2,6 } };
/* �ð���� */

XMFLOAT3 Camera_F = XMFLOAT3((float)0, (float)0, (float)-4000);
XMVECTOR up = XMVectorSet(0, 1, 0, 0);
XMVECTOR Camera_V;
XMVECTOR Camera_LookAt;
XMMATRIX Camera_M;
/* ī�޶���� ���� */

XMVECTOR Axis; float angle = 0;
/* ȸ������ ���� */

bool paint_trigger = false, lbutton = false, rbutton = false;
bool box_rotate = false, camera_rotate = false;
/* trigger ���� */

int oldPx = 0, oldPy = 0;
int Px = 0, Py = 0;
/* mouse��ǥ ���� */

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void handing_WM_CREATE(HWND, UINT, WPARAM, LPARAM);
void handing_WM_PAINT(HWND, UINT, WPARAM, LPARAM);
void handing_WM_KEYDOWN(HWND, UINT, WPARAM, LPARAM);
void QUIT(HWND, UINT, WPARAM, LPARAM);
FLOAT inline abs(FLOAT F) { return F < 0 ? F * -1 : F; }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	LPCWSTR ClassName = TEXT("doki_doki_literature_club");
	LPCWSTR Title = TEXT("�αٵα�");

	g_hInst = hInstance;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowW(ClassName, Title, WS_BORDER | WS_MINIMIZEBOX | CS_DBLCLKS, 0, 0, 1920, 1080, NULL, NULL, hInstance, NULL);
	if (!hWnd) return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (box_rotate) {
			XMMATRIX M = XMMatrixRotationAxis(Axis, XMConvertToRadians(angle));
			for (int i = 0; i < 8; i++)
				CUBE.V[i] = XMVector3TransformCoord(CUBE.V[i], M);
			paint_trigger = true;
			box_rotate = false;
		}
		else if (camera_rotate) {
			XMMATRIX M = XMMatrixRotationY(XMConvertToRadians(oldPx - Px) / (float)8);
			Camera_LookAt = XMVector3TransformCoord(Camera_LookAt - Camera_V, M) + Camera_V;
			M = XMMatrixRotationX(XMConvertToRadians(Py - oldPy) / (float)8);
			Camera_LookAt = XMVector3TransformCoord(Camera_LookAt - Camera_V, M) + Camera_V;

			Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
			paint_trigger = true;
			oldPx = Px; oldPy = Py;
			camera_rotate = false;
		}
		else if (GetMessage(&msg, 0, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
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
	case WM_KEYDOWN:
		handing_WM_KEYDOWN(hWnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		Px = LOWORD(lParam);
		Py = HIWORD(lParam);
		if (wParam & MK_LBUTTON)
		{
			paint_trigger = true;
			if (lbutton) break;
			oldPx = LOWORD(lParam);
			oldPy = HIWORD(lParam);
			lbutton = true;
		}
		else if (wParam & MK_RBUTTON)
		{
			camera_rotate = true;
			if (rbutton) break;
			oldPx = LOWORD(lParam);
			oldPy = HIWORD(lParam);
			rbutton = true;
		}
		break;
	case WM_LBUTTONUP:
		if (!lbutton)
			break;
		lbutton = false;
		paint_trigger = true;
		break;
	case WM_RBUTTONUP:
		rbutton = false;
		break;
	case WM_DESTROY:
		QUIT(hWnd, uMsg, wParam, lParam);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 0:
			if (!paint_trigger)
				break;
			InvalidateRect(hWnd, NULL, true);
			paint_trigger = false;
			break;
		case 1:
			if (GetAsyncKeyState('W') & 0x8000) Camera_V = XMVector3Normalize(Camera_LookAt) * 50 + Camera_V;
			if (GetAsyncKeyState('A') & 0x8000) Camera_V = XMVector3Normalize(XMVector3Cross(Camera_LookAt, up)) * 50 + Camera_V;
			if (GetAsyncKeyState('D') & 0x8000) Camera_V = XMVector3Normalize(XMVector3Cross(up, Camera_LookAt)) * 50 + Camera_V;
			if (GetAsyncKeyState('S') & 0x8000) Camera_V = XMVector3Normalize(Camera_LookAt) * -50 + Camera_V;
			Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
			paint_trigger = true;
			break;
		}
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
	SetTimer(hWnd, 0, 1000 / 45, NULL); //45������
	SetTimer(hWnd, 1, 1000 / 40, NULL); //wasd�Է�
	Camera_V = XMLoadFloat3(&Camera_F);
	Camera_LookAt = XMVectorSet(0, 0, 1, 0);
	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
	return;
}

void handing_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(hWnd, &ps);

	//������۸�
	RECT client_size; GetClientRect(hWnd, &client_size);
	HDC hdc = CreateCompatibleDC(h_dc);
	HBITMAP mem_new = CreateCompatibleBitmap(hdc, client_size.right, client_size.bottom);
	HBITMAP mem_old = (HBITMAP)SelectObject(hdc, mem_new);

	//���̾� ���� �غ�
	HPEN NewP, OldP;
	NewP = (HPEN)GetStockObject(WHITE_PEN);
	OldP = (HPEN)SelectObject(hdc, NewP);

	//6���� ���� ������
	for (int i = 0; i < 6; i++)
	{
		//�ĸ鼱��, ��������
		XMVECTOR
			v1 = XMVector3TransformCoord(CUBE.V[index[i][0]], Camera_M),
			v2 = XMVector3TransformCoord(CUBE.V[index[i][1]], Camera_M),
			v3 = XMVector3TransformCoord(CUBE.V[index[i][2]], Camera_M),
			v4 = XMVector3TransformCoord(CUBE.V[index[i][3]], Camera_M);
		XMVECTOR normal = XMVector3Cross(v1 - v2, v1 - v4);
		if (XMVectorGetX(XMVector3Dot(normal, (v1 * 3 / 2) - (v2 / 2))) > 0) continue;

		//�鸶�� �ִ� 4���� �����𼭸��� ������
		for (int j = 0; j < 4; j++)
		{
			XMVECTOR
				v1 = XMVector3TransformCoord(CUBE.V[index[i][j]], Camera_M),
				v2 = XMVector3TransformCoord(CUBE.V[index[i][(j + 1) == 4 ? 0 : j + 1]], Camera_M);

			//2�������� ���� �ű�
			//ī�޶� = ������ ȭ������� �Ÿ��� DISTANCE�� ����
			//DISTANCE�� Ŭ���� ��ü�� ũ�Ժ���
			FLOAT
				X1 = XMVectorGetX(v1) * (FLOAT)DISTANCE / XMVectorGetZ(v1) + 960,
				Y1 = XMVectorGetY(v1) * (FLOAT)DISTANCE / XMVectorGetZ(v1) + 540,
				X2 = XMVectorGetX(v2) * (FLOAT)DISTANCE / XMVectorGetZ(v2) + 960,
				Y2 = XMVectorGetY(v2) * (FLOAT)DISTANCE / XMVectorGetZ(v2) + 540;

			//���� 9���� ��´�
			COLORREF C = RGB(255, 255, 255);
			for (int i = -1; i < 2; i++)
				for (int j = -1; j < 2; j++)
					SetPixel(hdc, (int)X1 + i, (int)Y1 + j, C);

			MoveToEx(hdc, (int)X1, (int)Y1, NULL);
			LineTo(hdc, (int)X2, (int)Y2);
		}
	}
	SelectObject(hdc, OldP);
	/* ���� ��� ��! */

	if (lbutton)
	{
		NewP = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
		OldP = (HPEN)SelectObject(hdc, NewP);
		MoveToEx(hdc, oldPx, oldPy, NULL);
		LineTo(hdc, Px, Py);
		SelectObject(hdc, OldP);
	}

	BitBlt(h_dc, 0, 0, client_size.right, client_size.bottom, hdc, 0, 0, SRCCOPY);
	mem_new = (HBITMAP)SelectObject(hdc, mem_old);

	DeleteObject(mem_new);
	DeleteDC(hdc);
	EndPaint(hWnd, &ps);
	return;
}

void handing_WM_KEYDOWN(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_ESCAPE:
		QUIT(hWnd, uMsg, wParam, lParam);
		break;
	case VK_UP:
		Axis = XMVectorSet(1, 0, 0, 0); goto SET_ANGLE;
	case VK_DOWN:
		Axis = XMVectorSet(-1, 0, 0, 0); goto SET_ANGLE;
	case VK_LEFT:
		Axis = XMVectorSet(0, -1, 0, 0); goto SET_ANGLE;
	case VK_RIGHT:
		Axis = XMVectorSet(0, 1, 0, 0); goto SET_ANGLE;
	SET_ANGLE:
		angle = 1;
		box_rotate = true;
		break;
	}
	return;
}

void QUIT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	KillTimer(hWnd, 0);
	PostQuitMessage(0);
	return;
}