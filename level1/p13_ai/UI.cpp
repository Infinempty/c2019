#include"UI.h"
#include"AI.h"
int winner = PNULL;
extern unsigned char chessMap[BOARD_SIZE][BOARD_SIZE];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //������Ϣ������(����windows�ͽ���windows��Ϣ)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin"); //������
	HWND hwnd;//���
	MSG msg;//��Ϣ��
	WNDCLASS wndclass;//����һ��������ʵ��
	//���ô������
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //��ʽ
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;//����ʵ��������windows�Զ��ַ�
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//��ʾ�����ͼ��titlte
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//���ڹ��
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����ˢ
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;//���ô������windws��Ϣ����
	wndclass.lpszClassName = szAppName;//��������
	if (!RegisterClass(&wndclass))//ע�ᴰ����
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	};
	//����һ�����塣�ѷ����ڴ档����һ��������
	hwnd = CreateWindow(szAppName,      // window class name
		TEXT("�����磨���棩"),   // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT,// initial x position
		CW_USEDEFAULT,// initial y position
		610,// initial x size
		610,// initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL);
	ShowWindow(hwnd, iCmdShow);//��ʾ����
	UpdateWindow(hwnd);//���´���
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//������Ϣ�����͵�windows��Ϣ����
		DispatchMessage(&msg);//������Ϣ
	}
	return msg.wParam;
}
HRESULT GetXY(POINT zero, int cxClient, int cyClient, int *cxCell, int *cyCell)
{
	/*һ��15*15���� ��ÿ��С��ƽ������ ��Ȼ���鷳���ǿ��������������*/
	*cxCell = (cxClient - zero.x * 2) / (BOARD_SIZE - 1);
	*cyCell = (cyClient - zero.y * 2) / (BOARD_SIZE - 1);
	return S_OK;
}
HRESULT DrawChess(HDC hdc,POINT zero, POINT down,int cxclient,int cyclient,int color)
{
	if(color==PLAYER)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	else if(color==AI)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	int perx, pery, rx, ry;
	GetXY(zero, cxclient, cyclient, &perx, &pery);
	rx = perx *0.4;
	ry = pery *0.4;
	Ellipse(hdc, zero.x + down.x*perx - rx, zero.y + down.y*pery - ry, zero.x + down.x*perx + rx, zero.y + down.y*pery + ry);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	return S_OK;
}
HRESULT DrawChessBoard(HDC hdc, POINT zero, int cxClient, int cyClient)
{
	// ���һС��Ŀ�Ⱥ͸߶�
	int cxCell = 0, cyCell = 0;
	GetXY(zero, cxClient, cyClient, &cxCell, &cyCell);
	// ��������
	for (int col = 0; col < BOARD_SIZE; ++col) {
		MoveToEx(hdc, zero.x + col * cxCell, zero.y, NULL);
		LineTo(hdc, zero.x + col * cxCell, zero.y + (BOARD_SIZE - 1) * cyCell);
	}
	//���ƺ���
	for (int row = 0; row < BOARD_SIZE; ++row) {
		MoveToEx(hdc, zero.x, zero.y + row  * cyCell, NULL);
		LineTo(hdc, zero.x + (BOARD_SIZE - 1) * cxCell, zero.y + row * cyCell);
	}
	return S_OK;
}
HRESULT ChangePosition(POINT actual, POINT zero,POINT *truePosi,int clientx,int clienty)
{
	int perx, pery,min_distance,near_posi,xcount=0,ycount=0;
	double distance[4];
	POINT board_max;
	POINT temp[4];
	GetXY(zero, clientx, clienty, &perx, &pery);
	board_max.x = zero.x + (BOARD_SIZE - 1)*perx;
	board_max.y = zero.y + (BOARD_SIZE - 1)*pery;
	if (actual.x<zero.x || actual.x>board_max.x || actual.y<zero.y || actual.y>board_max.y)
	{
		MessageBox(NULL, TEXT("����������"), TEXT("����"), MB_OK);
		return S_FALSE;
	}
	for (int x = zero.x;; x += perx,xcount++)
	{
		if (x <= actual.x&&x + perx > actual.x)
		{
			temp[0].x = x;
			temp[2].x = x;
			temp[1].x = x + perx;
			temp[3].x = x + perx;
			break;
		}
	}
	for (int y = zero.y;; y += pery,ycount++)
	{
		if (y <= actual.y&&y + pery > actual.y)
		{
			temp[0].y = y;
			temp[1].y = y;
			temp[2].y = y + pery;
			temp[3].y = y + pery;
			break;
		}
	}
	for (int i = 0; i < 4; i++)distance[i] = pow(abs(temp[i].x - actual.x), 2) + pow(abs(temp[i].y - actual.y), 2);
	min_distance = distance[0];
	near_posi = 0;
	for (int i = 0; i < 4; i++)
	{
		if (distance[i] < min_distance)
		{
			min_distance = distance[i];
			near_posi = i;
		}
	}
	switch (near_posi)
	{
	case 1:
		xcount++;
		break;
	case 2:
		ycount++;
		break;
	case 3:
		xcount++;
		ycount++;
		break;
	default:
		break;
	}
	truePosi->x = xcount;
	truePosi->y = ycount;
	if (chessMap[xcount][ycount] != PNULL)
	{
		MessageBox(NULL, TEXT("�˴��Ѿ�����"), TEXT("��ʾ"), MB_OK);
		return S_FALSE;
	}
	return S_OK;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)//��Ϣ�Ĵ������
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	POINT actual,computer;
	POINT truePoint;
	POINT zero;
	zero.x = 30;
	zero.y = 40;
	int perx, pery;
	static int clientx, clienty;
	HRESULT hresult= S_FALSE;
	switch (message)
	{
	case WM_SIZE:
		/*��ȡ�����*/
		clientx = LOWORD(lParam);
		clienty = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		if (winner != PNULL)
		{
			MessageBox(hwnd, TEXT("���ֱ����Ѿ����������м��������̿�ʼ����һ�ֱ���"), TEXT("��ʾ"), MB_OK);
			return 0;
		}
		GetXY(zero, clientx, clienty, &perx, &pery);
		actual.x = LOWORD(lParam);
		actual.y = HIWORD(lParam);
		hresult=ChangePosition(actual,zero,&truePoint,clientx,clienty);
		if(hresult==S_FALSE)return 0;
		hdc = GetDC(hwnd);
		DrawChess(hdc,zero, truePoint,clientx,clienty,PLAYER);
		ReleaseDC(hwnd, hdc);
		chessMap[truePoint.x][truePoint.y] = PLAYER;
		if (judge(truePoint, PLAYER)==true)
		{
			winner = PLAYER;
			MessageBox(hwnd, TEXT("�˻�ʤ��"), TEXT("��ʾ"), MB_OK);
			return 0;
		}
		computer = AIturn();
		hdc = GetDC(hwnd);
		DrawChess(hdc, zero, computer, clientx, clienty, AI);
		ReleaseDC(hwnd, hdc);
		chessMap[computer.x][computer.y] = AI;
		if (judge(computer, AI) == true)
		{
			winner = AI;
			MessageBox(hwnd, TEXT("���Ի�ʤ��"), TEXT("��ʾ"), MB_OK);
			return 0;
		}
		//������ʱ���ִ��
	case WM_RBUTTONDOWN:
		return 0;
		//�Ҽ���ִ���κβ���
	case WM_MBUTTONDOWN:
		//�м����¿�ʼ  ���������ʤ�� ��ʼ������ 
		winner = PNULL;
		restart();
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		//һ��ʼ�Ļ�ͼ
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		DrawChessBoard(hdc, zero, clientx, clienty);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
void restart()
{
	memset(chessMap, 0, sizeof(chessMap));
}
bool judge(POINT down, char color)
{
	int count = 1, jtemp,m=0,n=0;
	for (int i = (down.x - 4 > 0 ? down.x - 4 : 0); i <= down.x + 4&&i<BOARD_SIZE; i++)
	{
		if (chessMap[i][down.y] == color)
		{
			count++;
			if (count >= 5)return true;
		}
		else count=0;
	}
	count = 0;
	for (int i = (down.y - 4 > 0 ? down.y - 4 : 0); i <= down.y + 4&&i<BOARD_SIZE; i++)
	{
		if (chessMap[down.x][i] == color)
		{
			count++;
			if (count >= 5)return true;
		}
		else count=0;
	}
	count = 0;
	for (jtemp = 0; jtemp <= 4; jtemp++)
	{
		if (down.x - jtemp == 0 || down.y - jtemp == 0)break;
	}
	for (m = down.x - jtemp, n = down.y - jtemp; m <= down.x + 4 && n <= down.y + 4 && m < BOARD_SIZE&&n < BOARD_SIZE; m++, n++)
	{
		if (chessMap[m][n] == color)
		{
			count++;
			if (count >= 5)return true;
		}
		else count=0;
	}
	count = 0;
	for (jtemp = 0; jtemp <= 4; jtemp++)
	{
		if (down.x - jtemp == 0 || down.y + jtemp == BOARD_SIZE-1)break;
	}
	for (m = down.x - jtemp, n = down.y + jtemp; m <= down.x + 4 && n >= down.y - 4 && m < BOARD_SIZE&&n >=0; m++, n--)
	{
		if (chessMap[m][n] == color)
		{
			count++;
			if (count >= 5)return true;
		}
		else count=0;
	}
	return false;
}