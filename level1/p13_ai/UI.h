#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PACK_STRUCT __attribute__((packed))
#define BOARD_SIZE   15//���̴�СΪ15x15
#define FIVE_MARK_POINT_RADIUS 4
//�ڰ׿���������
#define PNULL  0
#define AI 1
#define PLAYER 2
#define check(x)    (((x)<0) || ((x)>=BOARD_SIZE))
//����
extern unsigned char chessMap[BOARD_SIZE][BOARD_SIZE];
void restart();
bool judge(POINT, char);
