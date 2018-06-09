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
*/

#include <Windows.h>
#include <Windowsx.h>
#include <CommCtrl.h>
#include <process.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <vector>
#include "resource.h"

using namespace DirectX;
using namespace DirectX::PackedVector;

//�ո� �ð����		:0123
//�޸� �ð����		:5476
//���� �ð����		:3740
//������ �ð����	:1562
//���� �ð����		:4510
//�Ʒ��� �ð����	:7326
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
	//8���� ���� ��ǥ
};

struct CUBE_struct {
	XMVECTOR V[8] = { NULL, }; //��ü���θ� �������� ��������
	XMVECTOR Accel = XMVectorZero();
	XMVECTOR Veloc = XMVectorZero();
};
/* ����ü ���� */

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
/* ���ν��� */

void LOG_print(LPCTSTR);
void LOG_print(int);
void LOG_print(float);
void LOG_setting(HWND, HINSTANCE);
void LOG_initialize(void*);
void LOG_destroy();
/* logâ ���� */

void FOV_setting(HWND, HINSTANCE);
void FOV_handling(WPARAM, LPARAM);
float FOV_get();
void FOV_destroy();
bool FOV_paint();
/* fov��Ʈ�� ���� */

void EDIT_setting(HWND, WPARAM);
void EDIT_setting(HWND, HINSTANCE);
LRESULT CALLBACK EDIT_proc(HWND, UINT, WPARAM, LPARAM);
bool EDIT_msg(MSG&);
void EDIT_destroy();
/* ��ü����â ���� */

bool is_bumped(XMVECTOR);
bool is_bumped(XMMATRIX);
void camera_rotating(FLOAT, FLOAT);
void setting();
bool is_hidden(int);
void physic_calc(bool);
void physic_reset();
void front(); void rear(); void left(); void right();
void update_matrix();
void get_point(int, int, POINT&, POINT&);
XMVECTOR get_transformed(int, int);
/* ��ü ��� ���� */

void handling_WM_CREATE(HWND, UINT, WPARAM, LPARAM);
void handling_WM_PAINT(HWND, UINT, WPARAM, LPARAM);
void handling_WM_MOUSEMOVE(HWND, UINT, WPARAM, LPARAM);
void handling_WM_LBUTTONUP(HWND, UINT, WPARAM, LPARAM);
void handling_WM_RBUTTONUP(HWND, UINT, WPARAM, LPARAM);
void handling_WM_DESTROY(HWND, UINT, WPARAM, LPARAM);
void handling_WM_COMMAND(HWND, UINT, WPARAM, LPARAM);
/* �޼����ڵ鸵 */

int inline _key(char C) { return GetAsyncKeyState(C) & 0x8000; }
int inline _key1(char C) { return (GetAsyncKeyState(C) & 0x8001) == 0x8001; }
/* �ζ����Լ� */

void Box_Translation(HWND, UINT, UINT_PTR, DWORD);
void Physic_Effects(HWND, UINT, UINT_PTR, DWORD);
void Camera_Movement(HWND, UINT, UINT_PTR, DWORD);
void Paint_Trigger(HWND, UINT, UINT_PTR, DWORD);
void Key_Check(HWND, UINT, UINT_PTR, DWORD);
/* Timer�ڵ鸵 */