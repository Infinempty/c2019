#include"UI.h"
#include"AI.h"
int winner = PNULL;
extern unsigned char chessMap[BOARD_SIZE][BOARD_SIZE];
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //声名消息处理函数(处理windows和接收windows消息)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin"); //窗体名
	HWND hwnd;//句柄
	MSG msg;//消息体
	WNDCLASS wndclass;//这义一个窗体类实例
	//设置窗体参数
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //样式
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;//窗体实例名，由windows自动分发
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//显示上面的图标titlte
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//窗口光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//背景刷
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;//设置窗体接收windws消息函数
	wndclass.lpszClassName = szAppName;//窗体类名
	if (!RegisterClass(&wndclass))//注册窗体类
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	};
	//创建一个窗体。已分配内存。返回一个窗体句柄
	hwnd = CreateWindow(szAppName,      // window class name
		TEXT("幻想乡（迫真）"),   // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT,// initial x position
		CW_USEDEFAULT,// initial y position
		610,// initial x size
		610,// initial y size
		NULL, // parent window handle
		NULL, // window menu handle
		hInstance, // program instance handle
		NULL);
	ShowWindow(hwnd, iCmdShow);//显示窗口
	UpdateWindow(hwnd);//更新窗体
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译消息并发送到windows消息队列
		DispatchMessage(&msg);//接收信息
	}
	return msg.wParam;
}
HRESULT GetXY(POINT zero, int cxClient, int cyClient, int *cxCell, int *cyCell)
{
	/*一共15*15棋盘 把每个小格都平均分配 虽然很麻烦但是可以适用所有情况*/
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
	// 获得一小格的宽度和高度
	int cxCell = 0, cyCell = 0;
	GetXY(zero, cxClient, cyClient, &cxCell, &cyCell);
	// 绘制竖线
	for (int col = 0; col < BOARD_SIZE; ++col) {
		MoveToEx(hdc, zero.x + col * cxCell, zero.y, NULL);
		LineTo(hdc, zero.x + col * cxCell, zero.y + (BOARD_SIZE - 1) * cyCell);
	}
	//绘制横线
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
		MessageBox(NULL, TEXT("请点击棋盘内"), TEXT("错误"), MB_OK);
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
		MessageBox(NULL, TEXT("此处已经有子"), TEXT("提示"), MB_OK);
		return S_FALSE;
	}
	return S_OK;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)//消息的处理程序
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
		/*获取长与宽*/
		clientx = LOWORD(lParam);
		clienty = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		if (winner != PNULL)
		{
			MessageBox(hwnd, TEXT("本局比赛已经结束，按中键重置棋盘开始另外一局比赛"), TEXT("提示"), MB_OK);
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
			MessageBox(hwnd, TEXT("人获胜！"), TEXT("提示"), MB_OK);
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
			MessageBox(hwnd, TEXT("电脑获胜！"), TEXT("提示"), MB_OK);
			return 0;
		}
		//点击左键时候的执行
	case WM_RBUTTONDOWN:
		return 0;
		//右键不执行任何操作
	case WM_MBUTTONDOWN:
		//中键重新开始  包括清零获胜者 初始化棋盘 
		winner = PNULL;
		restart();
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		//一开始的绘图
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