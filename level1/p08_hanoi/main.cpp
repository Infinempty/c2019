#include<iostream>
using namespace std;
void hanio(int,char,char,char);
void move(int,char,char);
unsigned long long times=0;
int main()
{
	int e=0;
	cout<<"������������";
	cin>>e;
	if(e>=2)hanio(e,'x','z','y');//��x��z ������y 
	else 
	{
		times++;
		cout<<"��1���̴�a�ƶ���cλ��"<<endl;
	}
	cout<<"һ���ƶ���"<<times<<"��"; 
	return 0; 
 } 
void hanio(int n,char from,char to,char depend)
{
	if(n==1)move(1,from,depend);
	else
	{
		hanio(n-1,from,to,depend);//����ʱ��Ҳ���Ǻ���������� ����ò���ƶ�����ֻ��Ҫ�Ȱ������Ĵ�x ��y �ٴ�y ��z�Ϳ����� 
		move(n,from,to);
		hanio(n-1,depend,from,to);
	}
}
void move(int n,char from,char to)
{
	cout<<"��"<<n<<"���̴�"<<from<<"�ƶ���"<<to<<"λ��"<<endl;
	times++;
}

