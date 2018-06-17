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
static VC cu;
static int num, paint_n;
/* 물체 */

static int index[6][5] = { { 0,1,2,3,0 },{ 5,4,7,6,5 },{ 3,7,4,0,3 },{ 1,5,6,2,1 },{ 4,5,1,0,4 },{ 7,3,2,6,7 } };
/* 시계방향 첨자 */

bool judge(POINT& A, POINT& B)
{
	return A.x < B.x;
}

int cross(POINT& O, POINT& A, POINT& B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

VP convex_hull(VP P)
{
	int k = 0;
	VP H(16);
	sort(P.begin(), P.end(), judge);

	for (int i = 0; i < 8; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	for (int i = 7, t = k + 1; i > 0; --i) {
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) < 0) k--;
		H[k++] = P[i - 1];
	}

	H.resize(k - 1);
	return H;
}

F pptol(POINT& A, POINT& B)
{
	FLOAT a, b;
	a = (A.y - B.y) / (A.x - B.x + 0.000001);
	b = -1 * A.x * a + A.y;
	return make_pair(a, b);
}

float scale(POINT A)
{
	return sqrtf(A.x * A.x + A.y * A.y);
}

float angle(POINT A, POINT O, POINT B)
{
	A.x -= O.x;
	A.y -= O.y;
	B.x -= O.x;
	B.y -= O.y;
	float dot = A.x * B.x + A.y * B.y;
	return acosf(dot / scale(A) / scale(B));
}

bool winding_num(VP& P, POINT O)
{
	float sum = 0;
	for (int i = 0; i < P.size() - 1; i++) {
		if (cross(O, P[i], P[i + 1]) > 0)
			sum += angle(P[i], O, P[i + 1]);
		else sum -= angle(P[i], O, P[i + 1]);
	}
	return fabsf(sum - 2 * (float)3.141592) < 0.001;
}

POINT point(F A, F B)
{
	int x = (B.second - A.second) / (A.first - B.first);
	int y = x * A.first + A.second;
	return{ x, y };
}

bool point_check(POINT O, POINT A, POINT B)
{
	if (A.x < B.x) {
		if (A.x < O.x && O.x < B.x)
			return true;
	}
	else if (B.x < O.x && O.x < A.x)
		return true;
	return false;
}

float length(POINT A, POINT B) {
	POINT P = { A.x - B.x, A.y - B.y };
	return scale(P);
}

bool judge1(PP A, PP B)
{
	return length(A.second, A.first) < length(B.second, B.first);
}

POINT middle(POINT A, POINT B)
{
	return{ (A.x + B.x) / 2, (A.y + B.y) / 2 };
}

void rendering()
{
	for (int n = 0; n < cu.size(); n++) {
		cu[n].P.clear();
		cu[n].ch.clear(); cu[n].chl.clear();
		cu[n].F.clear(); cu[n].pll.clear();
		for (int i = 0; i < 6; i++)
			cu[n].plane[i].clear();
	}

	for (int n = 0; n < cu.size(); n++) {
		for (int i = 0; i < 8; i++)
			cu[n].VV[i] = XMVector3TransformCoord(cu[n].V[i], Camera_M);
		for (int i = 0; i < 8; i++) {
			XMVECTOR v = cu[n].VV[i];
			FLOAT X, Y;
			X = (XMVectorGetX(v) / XMVectorGetZ(v) / tanf(FOV_get() / 2) * 1000 + display.x / 2);
			Y = (XMVectorGetY(v) / XMVectorGetZ(v) / tanf(FOV_get() / 2) * 1000 + display.y / 2);
			POINT P = { X,Y };
			cu[n].P.push_back(P);
		}
		cu[n].ch = convex_hull(cu[n].P);
		cu[n].ch.push_back(cu[n].ch[0]);
		
		for (int i = 0; i < cu[n].ch.size() - 1; i++)
			cu[n].chl.push_back(pptol(cu[n].ch[i], cu[n].ch[i+1]));
		cu[n].chl.push_back(cu[n].chl[0]);

		VF temp;
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++)
				temp.push_back(pptol(cu[n].P[index[i][j]], cu[n].P[index[i][j + 1]]));
			cu[n].pll.push_back(temp);
			temp.clear();
		}
	}

	int s = cu.size(), val = 0;
	vector<int> t(s, val);
	vector<vector<int>> dp(s, t);
	//동적 계획법이용
	//어떤물체가 어떤물체를 가리는지 판단
	for (int n = 0; n < s; n++)
		for (int m = 0; m < s; m++) {
			if (n == m || dp[n][m] == 1) continue;
			for (int i = 0; i < cu[n].P.size(); i++)
				if (winding_num(cu[n].ch, cu[m].P[i])) {
					dp[n][m] = 1;
					dp[m][n] = 1;
					//LOG_print(L"\r\n물체끼리 가려짐!");
					XMVECTOR center
						= (cu[n].V[index[0][0]]
							+ cu[n].V[index[0][2]]
							+ cu[n].V[index[2][0]]
							+ cu[n].V[index[2][2]]) / 4;
					FLOAT L = XMVectorGetX(XMVector3Length(cu[m].V[i]));
					FLOAT D = XMVectorGetX(XMVector3Dot(center, cu[m].V[i]));
					if (D < L * L)
						cu[m].F.push_back(n);
					else
						cu[n].F.push_back(m);
				}
		}

	for (int m = 0; m < cu.size(); m++) {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
				cu[m].plane[i].push_back(cu[m].P[index[i][j]]);
				VPP temp;
				for (int k = 0; k < cu[m].F.size(); k++)
					for (int l = 0; l < cu[cu[m].F[k]].chl.size(); l++) {
						POINT P = point(cu[m].pll[i][j], cu[cu[m].F[k]].chl[l]);
						if (point_check(P, cu[m].P[index[i][j]], cu[m].P[index[i][j + 1]]))
							temp.push_back(make_pair(P, cu[m].P[index[i][j]]));
					}
				if (temp.size() > 1)
					sort(&temp[0], &temp[temp.size() - 1], judge1);
				for (int k = 0; k < temp.size(); k++)
					cu[m].plane[i].push_back(temp[k].first);
			}
			cu[m].plane[i].push_back(cu[m].plane[i][0]);
		}
	}
	return;
}

VP get_ch(int n)
{
	return cu[n].ch;
}

VPP get_plane(int m, int i)
{
	VPP Return;
	for (int k = 0; k < cu[m].plane[i].size() - 1; k++) {
		int R = 0;
		for (int l = 0; l < cu[m].F.size(); l++)
			if (winding_num(cu[cu[m].F[l]].ch, middle(cu[m].plane[i][k], cu[m].plane[i][k + 1])))
				R++;
		if (R == 0)
			Return.push_back(make_pair(cu[m].plane[i][k], cu[m].plane[i][k + 1]));
	}
	return Return;
}

bool is_bumped(XMVECTOR V)
{
	XMVECTOR T[8];
	for (int i = 0; i < 8; i++) {
		T[i] = cu[num].V[i] + V;
		if (XMVectorGetY(T[i]) < 0) {
			LOG_print(TEXT("\r\n땅에 부딪힘!"));
			return false;
		}
	}
	for (int i = 0; i < 8; i++) cu[num].V[i] = T[i];
	return true;
}

bool is_bumped(int num, XMVECTOR V)
{
	XMVECTOR T[8];
	for (int i = 0; i < 8; i++) {
		T[i] = cu[num].V[i] + V;
		if (XMVectorGetY(T[i]) < 0) {
			LOG_print(TEXT("\r\n땅에 부딪힘!"));
			return false;
		}
	}
	for (int i = 0; i < 8; i++) cu[num].V[i] = T[i];
	return true;
}

bool is_bumped(XMMATRIX M)
{
	XMVECTOR T[8];
	XMVECTOR Center = (cu[num].V[0] + cu[num].V[6]) / 2;
	for (int i = 0; i < 8; i++) {
		T[i] = XMVector3TransformCoord(cu[num].V[i] - Center, M) + Center;
		if (XMVectorGetY(T[i]) < 0) {
			LOG_print(TEXT("\r\n땅에 부딪힘!"));
			return false;
		}
	}
	for (int i = 0; i < 8; i++) cu[num].V[i] = T[i];
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
	create_new();
	Camera_M = XMMatrixLookAtLH(Camera_V, Camera_LookAt, up);
	return;
}

void create_new()
{
	CUBE_struct CUBE;
	XMVECTOR V = XMVectorSet(0, (float)1001, (float)3000 * (cu.size() + 1), 0);
	for (int i = 0; i < 8; i++)
		CUBE.V[i] = XMLoadFloat3(&(original_CUBE.F[i])) + V;
	cu.push_back(CUBE);
	num = (int)cu.size() - 1;
	return;
}

int cubes_num() { return (int)cu.size(); }
void set_paint_n(int n) { paint_n = n; }
void set_num(int n) { num = n == cu.size() ? 0 : n; }
int get_num() { return num; }

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
	for (int num = 0; num < cu.size(); num++) {
		static const XMVECTOR g = XMVectorSet(0, -9800, 0, 0);
		FLOAT T = 1 / (float)50;
		cu[num].Veloc += T * (is_g ? g + cu[num].Accel : cu[num].Accel);
		XMVECTOR V = cu[num].Veloc * T;
		if (!is_bumped(num, V))
			cu[num].Veloc *= XMVectorSet(1, -1, 1, 1);
	}
	return;
}

void physic_reset()
{
	for (int num = 0; num < cu.size(); num++)
		cu[num].Veloc = cu[num].Accel = XMVectorZero();
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
	return XMVector3TransformCoord(cu[paint_n].V[index[i][j]], Camera_M);
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