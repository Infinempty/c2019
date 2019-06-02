#include"AI.h"
#include"UI.h"
unsigned char chessMap[BOARD_SIZE][BOARD_SIZE];
POINT AIturn()
{
	a:POINT x;
	srand((unsigned)time(NULL));
	x.x = rand() % 15;
	x.y = rand() % 15;
	if (chessMap[x.x][x.y] != PNULL)goto a;
	return x;
}