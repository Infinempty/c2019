#include<iostream>
#include<conio.h>
#include<string.h>
#define MAPLE_X 11 //MAPLE_X �� MAPLE_Y ������ ���Ϳ�  
#define MAPLE_Y 23  //��ͼ�ֶ�������in.txt�ļ������� 
#define P players
#include<Windows.h>
using namespace std;
struct position
{
	int x,y;
};
struct objects
{
	int zt;
};
extern objects map[MAPLE_X+1][MAPLE_Y+1];
extern position players;
void scan();
void print();
void maze_move();
void judge();
