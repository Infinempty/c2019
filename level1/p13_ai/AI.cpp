#include"AI.h"
#include"UI.h"
chess_queue bests = { 0 };
//这是给定子数量和空位返回得分的
static int count_score(int count, int empty)
{
	if (count >= 5)return WIN;
	else if (count == 4)
	{
		if (empty == 2)return ALIVE4;
		else if(empty==1)return DIE4;
	}
	else if (count == 3)
	{
		if (empty == 2)return ALIVE3;
		else if (empty == 1) return DIE3;
	}
	else if (count == 2)
	{
		if (empty == 2)return ALIVE2;
		else if (empty == 1) return DIE2;
	}
	else if (count == 1)
	{
		if(empty==2)return ALIVE1;
	}
	return 0;
}
//对一行、一列、一条斜线、一条反斜线返回变量
static int count_num(char chess[],int num,char color)
{
	int count = 0, empty = 2, score = 0;
	if (chess[0] == color)
	{
		count++;
		empty--;
	}
	for (int i = 1; i < num; i++)
	{
		if (chess[i]==color)
		{
			if (count == 0)
			{
				if (chess[i - 1] == PNULL)
				{
					count++;
				}
				else
				{
					empty--;
					count++;
				}
			}
			else if (i == num - 1)
			{
				count++;
				empty--;
			}
			else
				count++;
		}
		else if (chess[i] != color)
		{
			if (count == 0)continue;
			else if (chess[i] == PNULL)
			{
				score += count_score(count, empty);
				count = 0;
				empty = 2;
			}
			else
			{
				empty--;
				score += count_score(count, empty);
				count = 0;
				empty = 1;
			}
		}
	}
	return score;
}
//对全局的评分
int evaluate(char color)
{
	char valu[15];
	int num = 15, score = 0, x = 0, y = 0;
	//行
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			valu[j] = chessMap[i][j];
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
	}
	//列
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			valu[j] = chessMap[j][i];
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
	}
	//正斜线
	for (int i = 0; i<BOARD_SIZE; i++)
	{
		for (x = i, y = 0; x < BOARD_SIZE&&y < BOARD_SIZE; x++, y++)
		{
			valu[y] = chessMap[x][y];
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
		num--;
	}
	num = 14;
	for (int i = 1; i < BOARD_SIZE; i++)
	{
		for (x = i, y = 0; x < BOARD_SIZE&&y < BOARD_SIZE; x++, y++)
		{
			valu[y] = chessMap[y][x];
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
		num--;
	}
	num = 1;
	//反斜线
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (x = i, y = 0; x >= 0 && y < BOARD_SIZE; x--, y++)
		{
			valu[y] = chessMap[x][y];
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
		num++;
	}
	num = 14;
	for (int i = 1; i<BOARD_SIZE; i++)
	{
		int temp = 0;
		for (x = i, y = 14; x <BOARD_SIZE && y >=0; x++, y--)
		{
			valu[temp] = chessMap[x][y];
			temp++;
		}
		score += count_num(valu, num, color);
		memset(valu, 0, sizeof(valu));
		num--;
	}
	return score;
}
static bool neigbor(int x, int y)
{
	int r = 2;
	for (int i = (x - r > 0 ? x - r : 0); i < x + r; i++)
	{
		for (int j = (y - r > 0 ? y - r : 0); j < y + r; j++)
		{
			if (chessMap[i][j] != PNULL)return true;
		}
	}
	return false;
}
static void generator(chess_queue* queue)
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (chessMap[i][j] != PNULL)continue;
			else if (neigbor(i, j))
			{
				queue->queue[queue->length].x = i;
				queue->queue[queue->length].y = j;
				queue->length++;
			}
		}
	}
}
static int AI_chess_score(int depth,int alpha,int beta)//(max层)
{
	/*站在alpha层考虑beta值 无论自己怎么下得分一般都不会超过beta  那么如果出现了得分比Beta大的也没必要搜索了 因为对方不会下这步*/
	int score, bestScore=-WIN,tempScore;
	chess_queue ch_queue = { 0,{0,0} };
	generator(&ch_queue);
	score = evaluate(AI)-evaluate(PLAYER);
	if (depth <= 0)return score;
	for (int i = 0; i < ch_queue.length; i++)
	{
		chessMap[ch_queue.queue[i].x][ch_queue.queue[i].y] = AI;
		tempScore = PLAYER_chess_score(depth - 1,alpha, (beta<bestScore?beta:bestScore));
		chessMap[ch_queue.queue[i].x][ch_queue.queue[i].y] = PNULL;
		if (tempScore > bestScore)
		{
			if (depth == DEPTH)
			{
				bests.length = 1;
				bests.queue[bests.length].x = ch_queue.queue[i].x;
				bests.queue[bests.length].y = ch_queue.queue[i].y;
			}
			bestScore = tempScore;
		}
		if (depth == DEPTH&&tempScore==bestScore)
		{
			bests.length++;
			bests.queue[bests.length].x = ch_queue.queue[i].x;
			bests.queue[bests.length].y = ch_queue.queue[i].y;
		}
		if (tempScore > alpha)break;
	}
	return bestScore;
}
static int PLAYER_chess_score(int depth, int alpha, int beta)
{
	int score, bestScore = WIN, tempScore;
	chess_queue ch_queue = { 0 };
	generator(&ch_queue);
	score = evaluate(AI) - evaluate(PLAYER);
	if (depth <= 0)return score;
	for (int i = 0; i < ch_queue.length; i++)
	{
		chessMap[ch_queue.queue[i].x][ch_queue.queue[i].y] = PLAYER;
		tempScore = AI_chess_score(depth - 1, (alpha < bestScore ? bestScore : alpha), beta);
		chessMap[ch_queue.queue[i].x][ch_queue.queue[i].y] = PNULL;
		if (tempScore < bestScore)bestScore = tempScore;
		if (tempScore < beta)break;
	}
	return bestScore;
}
POINT AIturn()
{
	POINT x;
	AI_chess_score(DEPTH, WIN, -WIN);
	srand((unsigned)time(NULL));
	int temp = rand() % bests.length+1;
	x.x = bests.queue[temp].x;
	x.y = bests.queue[temp].y;
	return x;
}