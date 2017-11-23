/*
                        *%%::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.
                      *@V[4]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+
                    *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[5]#
                  +@@@@@@@@@                                                          +@@@@@@.
                *@@@@@++@@@@                                                        *@@@@@@@@.
              *@@@@@+  =@@@@                                                      *@@@@@+@@@@.
            +@@@@@*    =@@@@                                                    *@@@@@+  @@@@.
          *@@@@@+      =@@@@                                                  *@@@@@+    @@@@.
        *@@@@@+        +@@@@                                                *@@@@@+      @@@@.
      *@@@@@*          .%@@*                                              #@@@@@+        @@@@.
    *@@@@@+                                                             *@@@@@+          @@@@.
 :*@@@@@%:.:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*@@@@@+            @@@@.
=V[0]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[1]=              @@@@.
=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@               @@@@.
=@@@@                                                                +@@@@               @@@@.
=@@@@                   .==                                          *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                    ..                                          *@@@@               @@@@.
=@@@@                                                                *@@@@               @@@@.
=@@@@                                                                *@@@@               @@@@.
=@@@@                    ::                                          *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@               @@@@.
=@@@@                  =@@@@                                         *@@@@  .++++++++++++@@@@@@=
=@@@@                  =@@@@    =@@@@@@@@@@@@@@.   #@@@@@@@@@@@@@@@= *@@@@ +@@@@@@@@@@@@@@@@@@@@
=@@@@                  :V[7]    +@@@@@@@@@@@@@@:   @@@@@@@@@@@@@@@@* *@@@@  *%%%%%%%%##@@V[6]@:
=@@@@                    ..       ............      ..............   *@@@@            #@@@@@:
=@@@@                                                                *@@@@         .%@@@@@:
=@@@@        ..                                                      *@@@@       .%@@@@@:
=@@@@      .#@@@=                                                    *@@@@    .%%@@@@@:
=@@@@    .%@@@@@:                                                    *@@@@  .%@@@@@@:
=@@@@  .%@@@@@:                                                      *@@@@ %@@@@@:
=@@@@.%@@@@@=                                                        *@@@@@@@@@=
=@@@@@@@@%.                                                          +@@@@@@@=
=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:
=V[3]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@V[2]
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 오른쪽으로 갈수록 x증가
 위로 갈수록 y증가
 뒤로 갈수로 z증가
 각각의 모서리는 길이2
*/



#include <Windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

#define DISTANCE 700
#define INDEX 15
#define ALLOWABLE_ERROR 10

//앞면 시계방향	:0123
//뒷면 시계방향	:5476
//왼편 시계방향	:3740
//오른편 시계방향	:1562
//윗면 시계방향	:4510
//아랫면 시계방향	:7326
//시계방향이 아니게된 면은 렌더링안함
struct CUBE_struct
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
	//8개의 점의 좌표

	XMVECTOR V[8] = { NULL, }; //물체내부를 (0.0)으로 잡은상태
	XMVECTOR V1[8] = { NULL, }; //2차원으로 투영시킨상태
}CUBE;

int index[6][4] = { { 0,1,2,3 },{ 5,4,7,6 },{ 3,7,4,0 },{ 1,5,6,2 },{ 4,5,1,0 },{ 7,3,2,6 } };
/* 시계방향 판별용 */

XMFLOAT3 Camera_F = XMFLOAT3((float)0, (float)0, (float)-3000);
XMVECTOR Camera_V;
XMMATRIX Camera_M;
/* 카메라관련 변수 */

XMVECTOR Axis; float angle = 0;
/* 회전관련 변수 */

bool paint_trigger = false, state = false, mouse_state = false;
/* trigger 변수 */

int oldPx = 0, oldPy = 0;
int Px = 0, Py = 0;
/* mouse좌표 변수 */

HINSTANCE g_hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void handing_WM_CREATE(HWND, UINT, WPARAM, LPARAM);
void handing_WM_PAINT(HWND, UINT, WPARAM, LPARAM);
void handing_WM_KEYDOWN(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
	LPCWSTR ClassName = TEXT("호옹이");
	LPCWSTR Title = TEXT("두근두근");

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
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (state)
		{
			XMMATRIX M = XMMatrixRotationAxis(Axis, XMConvertToRadians(angle));
			for (int i = 0; i < 8; i++)
				CUBE.V[i] = XMVector3TransformCoord(CUBE.V[i], M);
			state = false;
			paint_trigger = true;
		}
		else if (GetMessage(&msg, 0, 0, 0))
		{
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
	case WM_LBUTTONDOWN:
		mouse_state = true;
		oldPx = LOWORD(lParam);
		oldPy = HIWORD(lParam);
		break;
	case WM_LBUTTONDBLCLK:
		Px = LOWORD(lParam);
		Py = HIWORD(lParam);
		paint_trigger = true;
		break;
	case WM_LBUTTONUP:
		mouse_state = false;
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
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
		CUBE.V[i] = XMLoadFloat3(&(CUBE.F[i]));
	SetTimer(hWnd, 0, 30, NULL);
	Camera_V = XMLoadFloat3(&Camera_F);
	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	Camera_M = XMMatrixLookAtLH(Camera_V, target, up);
	return;
}

void handing_WM_PAINT(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC h_dc = BeginPaint(hWnd, &ps);

	//더블버퍼링
	RECT client_size; GetClientRect(hWnd, &client_size);
	HDC hdc = CreateCompatibleDC(h_dc);
	HBITMAP mem_new = CreateCompatibleBitmap(hdc, client_size.right, client_size.bottom);
	HBITMAP mem_old = (HBITMAP)SelectObject(hdc, mem_new);

	//하얀 선을 그리기 위해 하얀펜을 준비
	HPEN NewP, OldP;
	NewP = (HPEN)GetStockObject(WHITE_PEN);
	OldP = (HPEN)SelectObject(hdc, NewP);

	//시야 좌표계로 변환
	for (int i = 0; i < 8; i++)
		CUBE.V1[i] = XMVector3TransformCoord(CUBE.V[i], Camera_M);

	//6개의 면을 각각 렌더링
	for (int i = 0; i < 6; i++)
	{
		//시계방향이 아닌 = 뒤를 보고있는 면은 렌더링안함
		XMVECTOR V = XMVector3Cross((CUBE.V[index[i][1]] - CUBE.V[index[i][0]]), (CUBE.V[index[i][2]] - CUBE.V[index[i][0]]));
		if (XMVectorGetZ(V) + (FLOAT)ALLOWABLE_ERROR >= (FLOAT)0)
			continue;

		//한면마다 있는 4개의 점or모서리 를 렌더링
		for (int j = 0; j < 4; j++)
		{
			//카메라 = 원점과 화면사이의 거리를 DISTANCE로 놓음
			//DISTANCE가 클수록 물체가 크게보임
			FLOAT X = XMVectorGetX(CUBE.V1[index[i][j]]) * (FLOAT)DISTANCE / XMVectorGetZ(CUBE.V1[index[i][j]]) + 960;
			FLOAT Y = XMVectorGetY(CUBE.V1[index[i][j]]) * (FLOAT)DISTANCE / XMVectorGetZ(CUBE.V1[index[i][j]]) + 540;

			//점을 4개 찍는다
			COLORREF C = RGB(255, 255, 255);
			SetPixel(hdc, (int)X, (int)Y, C);
			SetPixel(hdc, (int)X + 1, (int)Y, C);
			SetPixel(hdc, (int)X + 1, (int)Y + 1, C);
			SetPixel(hdc, (int)X, (int)Y + 1, C);

			//INDEX를 조절해 하얀선분 길이조절
			//INDEX가 클수록 길이가 길어짐
			XMVECTOR V1 = (CUBE.V1[index[i][j]] - CUBE.V1[index[i][(j + 1) == 4 ? 0 : j + 1]]) / (FLOAT)INDEX + CUBE.V1[index[i][(j + 1) == 4 ? 0 : j + 1]];
			XMVECTOR V2 = (CUBE.V1[index[i][(j + 1) == 4 ? 0 : j + 1]] - CUBE.V1[index[i][j]]) / (FLOAT)INDEX + CUBE.V1[index[i][j]];

			FLOAT X1 = XMVectorGetX(V1) * (FLOAT)DISTANCE / XMVectorGetZ(V1) + 960;
			FLOAT Y1 = XMVectorGetY(V1) * (FLOAT)DISTANCE / XMVectorGetZ(V1) + 540;

			FLOAT X2 = XMVectorGetX(V2) * (FLOAT)DISTANCE / XMVectorGetZ(V2) + 960;
			FLOAT Y2 = XMVectorGetY(V2) * (FLOAT)DISTANCE / XMVectorGetZ(V2) + 540;

			MoveToEx(hdc, (int)X1, (int)Y1, NULL);
			LineTo(hdc, (int)X2, (int)Y2);
			/*선 출력 끝!*/
		}
	}
	/* 상자 출력 끝! */

	if (mouse_state)
	{
		NewP = CreatePen(PS_DASH, 1, RGB(255, 255, 255));
		OldP = (HPEN)SelectObject(hdc, NewP);
		MoveToEx(hdc, oldPx, oldPy, NULL);
		LineTo(hdc, Px, Py);
		SelectObject(hdc, OldP);
	}

	SelectObject(hdc, OldP);
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
		DestroyWindow(hWnd);
		break;
	case VK_UP:
		angle = 30;
		Axis = XMVectorSet(1, 0, 0, 0);
		state = true;
		break;
	case VK_DOWN:
		angle = 30;
		Axis = XMVectorSet(-1, 0, 0, 0);
		state = true;
		break;
	case VK_LEFT:
		angle = 30;
		Axis = XMVectorSet(0,-1, 0, 0);
		state = true;
		break;
	case VK_RIGHT:
		angle = 30;
		Axis = XMVectorSet(0, 1, 0, 0);
		state = true;
		break;
	}
	return;
}