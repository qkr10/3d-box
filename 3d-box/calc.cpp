#include "declarations.h"

static XMVECTOR up = XMVectorSet(0, -1, 0, 0);
static XMVECTOR Camera_V = XMVectorSet(0, 0, -8000, 0);
static XMVECTOR Camera_R = XMVectorSet(1, 0, 0, 0);
static XMVECTOR Camera_LookAt = XMVectorSet(0, 0, 1, 0);
static XMMATRIX Camera_M;
/* 카메라관련 변수 */

static POINT display = { 1980, 1080 };
/* 화면크기 저장용 */

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

XMVECTOR get_point(int i, int j)
{
	XMVECTOR v = get_transformed(i, j), P;

	//2차원으로 점을 옮김
	FLOAT X, Y;
	X = (XMVectorGetX(v) / XMVectorGetZ(v) / tanf(FOV_get() / 2) * 1000 + display.x / 2);
	Y = (XMVectorGetY(v) / XMVectorGetZ(v) / tanf(FOV_get() / 2) * 1000 + display.y / 2);
	P = XMVectorSet(X, Y, 0, 0);
	return P;
}

XMVECTOR get_transformed(int i, int j)
{
	return XMVector3TransformCoord(CUBE.V[index[i][j]], Camera_M);
}

void get_line(VV& dots, VV& lines)
{
	//내분점이용!
	int i = 1, LINE_NUM = LINE_NUM_get();
	while (i < LINE_NUM + 1)
	{
		lines.push_back(dots[1] * (FLOAT)i / LINE_NUM + dots[0] * (FLOAT)(LINE_NUM - i) / LINE_NUM);
		lines.push_back(dots[3] * (FLOAT)i / LINE_NUM + dots[0] * (FLOAT)(LINE_NUM - i) / LINE_NUM); i++;
	}
	i = 1;
	while (i < LINE_NUM)
	{
		lines.push_back(dots[2] * (FLOAT)i / LINE_NUM + dots[1] * (FLOAT)(LINE_NUM - i) / LINE_NUM);
		lines.push_back(dots[2] * (FLOAT)i / LINE_NUM + dots[3] * (FLOAT)(LINE_NUM - i) / LINE_NUM); i++;
	}
}

void set_display(RECT& rect)
{
	display.x = rect.right;
	display.y = rect.bottom;
	return;
}