#include "declarations.h"

bool is_bumped(XMVECTOR V)
{
	XMVECTOR T[8];
	for (int i = 0; i < 8; i++) {
		T[i] = CUBE.V[i] + V;
		if (XMVectorGetY(T[i]) < 0)
			return false;
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
		if (XMVectorGetY(T[i]) < 0)
			return false;
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
	XMVECTOR
		v1 = XMVector3TransformCoord(CUBE.V[index[i][0]], Camera_M),
		v2 = XMVector3TransformCoord(CUBE.V[index[i][1]], Camera_M),
		v3 = XMVector3TransformCoord(CUBE.V[index[i][2]], Camera_M),
		v4 = XMVector3TransformCoord(CUBE.V[index[i][3]], Camera_M);
	XMVECTOR normal = XMVector3Cross(v1 - v2, v1 - v4);
	if (XMVectorGetX(XMVector3Dot(normal, (v1 * 3 / 2) - (v2 / 2))) > 0)
		return true;
	if (XMVectorGetZ(v1) < 0 || XMVectorGetZ(v2) < 0 || XMVectorGetZ(v3) < 0 || XMVectorGetZ(v4) < 0)
		return true;
	return false;
}

