#include<iostream>
#include<ctime>
#define LE 166 //166����1000/6����ȡ���õ��� 
using namespace std;
int panduan(int);
void a();
bool judge=0; 
int main()
{
	clock_t start,end;
	start=clock();
	cout<<"2 3 ";//2��3��������6n-1��6n+1�� ����ȥ�� 
	for(int i=1;i<=LE;i++)
	{
		panduan(6*i-1);
		panduan(6*i+1);
	}
	//a();
	end=clock();
	cout<<endl<<"����ʱ����"<<(double)(end-start)/CLOCKS_PER_SEC<<"s"; 
	return 0;
}
int panduan(int in)
{
	judge=0;
	static int times=3;
	static int t[200]={0};
	t[1]=2;
	t[2]=3;
	for(int i=1;t[i]!=0;i++)if(in%t[i]==0)return 0;
	cout<<in<<" ";
	t[times]=in;
	times++;
}
/*void a()
{
	bool a[1001]={0};         //�����Ǳ����㷨
	for(int i=3;i<=1000;i++)
	{
		for(int j=2;j<i;j++)
		{
			if(i%j==0)a[i]=1;
		}
	}
	for(int i=1;i<=1000;i++)if(a[i]==0)cout<<i<<" ";
}*/
