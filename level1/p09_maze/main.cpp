#include"head.h"
objects map[MAPLE_X+1][MAPLE_Y+1];
position players;
int main()
{
	cout<<"*�Ŵ���ǽ��+�Ŵ�����ң�$�ź���Ȼ�����Ŀ�� wasd�ֱ����������� ����ENTER��ʼ"<<endl;
	system("pause");
	scan();
	char pt;
	while(1)
	{
		print(); 
		maze_move();
		if(map[P.x][P.y].zt==3)break;
	}
	cout<<endl<<"��Ӯ��";
	return 0;
}


