#include<iostream>
#define LE 100 //166����100/6����ȡ���õ��� 
using namespace std;
int prime(int);
int t[200]={0}; 
int main()
{
	for(int i=1;i<=LE/6;i++)//���ѭ�������� 
	{
		prime(6*i-1);
		prime(6*i+1);
	}
	for(int i=2;i<=LE;i+=2)//���ѭ����֤���� 
	{
		bool p=0;
		for(int j=1;t[j]!=0;j++)
		{
			for(int k=1;k<=j&&p==0;k++)
			{
				if(i==t[j]+t[k])
				{
					p=1;
					cout<<i<<"="<<t[k]<<"+"<<t[j]<<endl;
				}
			}
		}
	}
	return 0;
}
int prime(int in)//��ȡ�����б� 
{
	bool judge=0;
	static int times=3;
	t[1]=2;
	t[2]=3;
	for(int i=1;t[i]!=0;i++)if(in%t[i]==0)return 0;
	t[times]=in;
	times++;
}

