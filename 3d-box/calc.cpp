#include "declarations.h"

static XMVECTOR up = XMVectorSet(0, -1, 0, 0);
static XMVECTOR Camera_V = XMVectorSet(0, 0, -8000, 0);
static XMVECTOR Camera_R = XMVectorSet(1, 0, 0, 0);
static XMVECTOR Camera_LookAt = XMVectorSet(0, 0, 1, 0);
static XMMATRIX Camera_M;
/* 카메라관련 변수 */

static original_CUBE_struct original_CUBE;
static CUBE_struct CUBE;
/* 물체의 정점들 */

static int index[6][4] = { { 0,1,2,3 },{ 5,4,7,6 },{ 3,7,4,0 },{ 1,5,6,2 },{ 4,5,1,0 },{ 7,3,2,6 } };
/* 시계방향 첨자 */

bool is_bumped(XMVECTOR V)
{
	XMVECTOR T[8];
	for (int i = 0; i < 8; i++) {
		T[i] = CUBE.V[i] + V;
		if (XMVectorGetY(T[i]) < 0) {
			LOG_print(TEXT("\r\n땅에 부딪힘!"));
			return false;
		}
	}
	for (int i = 0; i < 8; i++) CUBE.V[i] = T[i];
	return true;
}

bool is_bumped(XMMATRIX M)
{
	XMVECTOR T[8];
	XMVECTOR Center = (CUBE.V[0] + CUBE.V[6]) / 2;
	for (int i = 0; i < 8; i++) {
		T[i] = XMVector3TransformCoord(CUBE.V[i] - Center, M) + Center;
		if (XMVectorGetY(T[i]) < 0) {
			LOG_print(TEXT("\r\n땅에 부딪힘!"));
			return false;
		}
	}
	for (int i = 0; i < 8; i++) CUBE.V[i] = T[i];
	return true;
}

void camera_rotating(FLOAT X, FLOAT Y)
{
	XMMATRIX M = XMMatrixRotationAxis(up, X);
	Camera_LookAt = XMVector3TransformCoord(Camera_LookAt, M);
	Camera_R = XMVector3Cross(Camera_LookAt, up);
	M = XMMatrixRotationAxis(Camera_R, Y);
	Camera_LookAt = XMVector3TransformCoord(Camera_LookAt, M);

	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt + Camera_V, up);
	return;
}

void setting()
{
	for (int i = 0; i < 8; i++)
		CUBE.V[i] = XMLoadFloat3(&(original_CUBE.F[i])) + XMVectorSet(0, (float)1000.000001, 0, 0);
	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
	return;
}

bool is_hidden(int i)
{
	//은면제거
	XMVECTOR v1 = get_transformed(i, 0), v2 = get_transformed(i, 1),
		v3 = get_transformed(i, 2), v4 = get_transformed(i, 3);
	XMVECTOR normal = XMVector3Cross(v1 - v2, v1 - v4);
	if (XMVectorGetX(XMVector3Dot(normal, (v1 * 3 / 2) - (v2 / 2))) > 0)
		return true;
	if (XMVectorGetZ(v1) < 0 || XMVectorGetZ(v2) < 0 || XMVectorGetZ(v3) < 0 || XMVectorGetZ(v4) < 0)
		return true;
	return false;
}

void physic_calc(bool is_g)
{
	static const XMVECTOR g = XMVectorSet(0, -9800, 0, 0);
	FLOAT T = 1 / (float)50;
	CUBE.Veloc += T * (is_g ? g + CUBE.Accel : CUBE.Accel);
	XMVECTOR V = CUBE.Veloc * T;
	if (!is_bumped(V))
		CUBE.Veloc *= XMVectorSet(1, -1, 1, 1);
	return;
}

void physic_reset()
{
	CUBE.Veloc = CUBE.Accel = XMVectorZero();
	return;
}

void front() { Camera_V += Camera_LookAt * 500; return; }
void left() { Camera_V += Camera_R * 500; return; }
void rear() { Camera_V += Camera_LookAt * -1 * 500; return; }
void right() { Camera_V += Camera_R * -1 * 500; return; }

void update_matrix()
{
	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt + Camera_V, up);
	return;
}

void get_point(int i, int j, POINT &P1, POINT &P2)
{
	XMVECTOR v1 = get_transformed(i, j), v2 = get_transformed(i, (j + 1) == 4 ? 0 : j + 1);

	//2차원으로 점을 옮김
	P1.x = (LONG)(XMVectorGetX(v1) / XMVectorGetZ(v1) / tanf(FOV_get() / 2) * 1000 + 960);
	P1.y = (LONG)(XMVectorGetY(v1) / XMVectorGetZ(v1) / tanf(FOV_get() / 2) * 1000 + 540);
	P2.x = (LONG)(XMVectorGetX(v2) / XMVectorGetZ(v2) / tanf(FOV_get() / 2) * 1000 + 960);
	P2.y = (LONG)(XMVectorGetY(v2) / XMVectorGetZ(v2) / tanf(FOV_get() / 2) * 1000 + 540);
	return;
}

XMVECTOR get_transformed(int i, int j)
{
	return XMVector3TransformCoord(CUBE.V[index[i][j]], Camera_M);
}