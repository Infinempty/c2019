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
class objects
{
	public:
		int zt;
};
int main()
{
	cout<<"*�Ŵ���ǽ��+�Ŵ�����ң�$�ź���Ȼ�����Ŀ�� wasd�ֱ����������� ����ENTER��ʼ"<<endl;
	system("pause");
	objects map[MAPLE_X+1][MAPLE_Y+1];
	position players;
	freopen("in.txt","r",stdin);
	for(int i=1;i<=MAPLE_X;i++)
	{
		for(int j=1;j<=MAPLE_Y;j++)
		{
			cin>>map[i][j].zt;
			if(map[i][j].zt==2)
			{
				players.x=i;
				players.y=j;
			}
		}
	}
	char pt;
	while(1)
	{
		for(int i=1;i<=MAPLE_X;i++)
		{
			for(int j=1;j<=MAPLE_Y;j++)
			{
				if(map[i][j].zt==0)cout<<" ";
				else if(map[i][j].zt==1)cout<<"*";
				else if(map[i][j].zt==2)cout<<"+";
				else if(map[i][j].zt==3)cout<<"$";
			}
			cout<<endl;
		}
		pt=getch();
		map[P.x][P.y].zt=0;
		if((pt=='w'||pt=='W')&&map[P.x-1][P.y].zt!=1)players.x-=1;
		else if((pt=='s'||pt=='S')&&map[P.x+1][P.y].zt!=1)players.x+=1;
		else if((pt=='a'||pt=='A')&&map[P.x][P.y-1].zt!=1)players.y-=1;
		else if((pt=='d'||pt=='D')&&map[P.x][P.y+1].zt!=1)players.y+=1;
		if(map[P.x][P.y].zt==3)break;
		map[players.x][players.y].zt=2;
		system("cls");
	}
	cout<<endl<<"��Ӯ��";
	return 0;
}


