#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PACK_STRUCT __attribute__((packed))
#define FALSE  0
#define TRUE   1 
#define BOARD_SIZE   25//棋盘大小为15x15
#define FIVE_MARK_POINT_RADIUS 4
#define CHESS_PIECE_RADIUS	13
//黑白空三种类型
#define PNULL  0
#define AI 1
#define PLAYER 2
#define check(x)    (((x)<0) || ((x)>=BOARD_SIZE))
//棋子

void restart();
bool judge(POINT, char);
