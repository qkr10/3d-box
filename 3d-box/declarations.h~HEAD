#pragma once
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
오른쪽으로 갈수록 x증가
위로 갈수록 y증가
뒤로 갈수로 z증가
각각의 모서리는 길이2000


=      y축                                               화면                                         :::::::
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
= :    원점(카메라)::::::::::::::::::::::::::::::::::::::::.%.:::::::::::::::::::::::::::::::::::::::::::::::::::z축
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
시야각(tan) : 16/9 ~ -16/9
*/

#include <Windows.h>
#include <Windowsx.h>
#include <process.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <stdlib.h>
#include <stdio.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

//앞면 시계방향		:0123
//뒷면 시계방향		:5476
//왼편 시계방향		:3740
//오른편 시계방향	:1562
//윗면 시계방향		:4510
//아랫면 시계방향	:7326
struct original_CUBE_struct {
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
};

struct CUBE_struct {
	XMVECTOR V[8] = { NULL, }; //물체내부를 원점으로 잡은상태
	XMVECTOR Accel = XMVectorZero();
	XMVECTOR Veloc = XMVectorZero();
};
/* 구조체 정의 */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/* 프로시저 */

void LOG_print(LPCTSTR);
void LOG_print(int);
void LOG_print(float);
void LOG_setting(HWND, HINSTANCE);
void LOG_destroy();
/* log창 관련 */

void FOV_setting(HWND, HINSTANCE);
void FOV_handling(WPARAM, LPARAM);
float FOV_get();
void FOV_destroy();
bool FOV_paint();
/* fov컨트롤 관련 */

void handling_WM_CREATE(HWND, UINT, WPARAM, LPARAM);
void handling_WM_PAINT(HWND, UINT, WPARAM, LPARAM);
void handling_WM_MOUSEMOVE(HWND, UINT, WPARAM, LPARAM);
void handling_WM_LBUTTONUP(HWND, UINT, WPARAM, LPARAM);
void handling_WM_RBUTTONUP(HWND, UINT, WPARAM, LPARAM);
void handling_WM_DESTROY(HWND, UINT, WPARAM, LPARAM);
/* 메세지핸들링 */

bool is_bumped(XMVECTOR);
bool is_bumped(XMMATRIX);
void camera_rotating(FLOAT, FLOAT);
void setting();
bool is_hidden(int);
void point_coor(int, POINT*);

static XMVECTOR up = XMVectorSet(0, -1, 0, 0);
static XMVECTOR Camera_V = XMVectorSet(0, 0, -8000, 0);
static XMVECTOR Camera_R = XMVectorSet(1, 0, 0, 0);
static XMVECTOR Camera_LookAt = XMVectorSet(0, 0, 1, 0);
static XMMATRIX Camera_M;
/* 카메라관련 변수 */

static original_CUBE_struct original_CUBE;
/* 물체의 정점들 */

static int index[6][4] = { { 0,1,2,3 },{ 5,4,7,6 },{ 3,7,4,0 },{ 1,5,6,2 },{ 4,5,1,0 },{ 7,3,2,6 } };
/* 시계방향 첨자 */

static CUBE_struct CUBE;

/* 계산 관련 */

FLOAT inline abs(FLOAT F) { return F < 0 ? F * -1 : F; }
int inline _key(char C) { return GetAsyncKeyState(C) & 0x8000; }
int inline _key1(char C) { return (GetAsyncKeyState(C) & 0x8001) == 0x8001; }
/* 인라인함수 */

void Box_Translation(HWND, UINT, UINT_PTR, DWORD);
void Physic_Effects(HWND, UINT, UINT_PTR, DWORD);
void Camera_Movement(HWND, UINT, UINT_PTR, DWORD);
void Paint_Trigger(HWND, UINT, UINT_PTR, DWORD);
void Key_Check(HWND, UINT, UINT_PTR, DWORD);
/* Timer핸들링 */