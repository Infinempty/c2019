#include<iostream>
using namespace std;
int main()
{
	long long in1=0;
	unsigned long long in=0,times=2;
	cout<<"����������Ҫ�жϵ���x 1<x<18446744073709551615"<<endl;
	cin>>in;
	if(in1<=2||in1!=(int)in1)
	{
		cout<<"��������"<<endl;
		return 0;
	}
	in=in1;
	for(times;times<in;times++)
	{
		if(in%times==0)
		{
			cout<<"����������";
			return 0;
		}
	}
	cout<<"��������"; 
	return 0;
}

