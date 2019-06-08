#include"UI.h"
#include<time.h>


#define DEPTH 3

#define WIN 100000
#define ALIVE4 20000
#define DIE4 2000
#define ALIVE3 1000
#define DIE3 100
#define ALIVE2 120
#define DIE2 11
#define ALIVE1 10

struct chess_queue
{
	int length;
	POINT queue[BOARD_SIZE*BOARD_SIZE+20];
};


int count_score(int, int);
int count_num(char chess[],int num,char color);
int evaluate(char color);
bool neigbor(int, int);
void generator(chess_queue);
int AI_chess_score(int,int,int);
int PLAYER_chess_score(int, int, int);
POINT AIturn();
