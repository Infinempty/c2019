#include <iostream>
#include<string.h> 
#include<cmath>
#include<Windows.h> 
using namespace std;
string lock(string,int);
int r_key[4]={0};
int main(int argc, char** argv) {
	string text=" ";
	string after=" ";
	int times=0,key=0,r=0;
	cout<<"���������ļ��ܻ�����ı�"<<endl;
	getline(cin,text);
	system("cls");
	cout<<"�������Ҫ���� ������1 ��������-1"<<endl;
	cin>>times;
	system("cls");
	cout<<"������������Կ��Ҫ���õ���Կ"<<endl;
	cin>>key;
	system("cls");
	for(int i=0;i<4;i++)
	{
		r=pow(10,i+1);
		r_key[i]=(key%r)/(r/10);
	}
	after=lock(text,times);
	cout<<"����/���ܺ����������"<<endl<<after<<endl;
	return 0;
}
string lock(string text,int times)
{
	for(int i=0;i<text.length();i++)
	{
		text[i]+=(r_key[i%4]*times);
	}
	return text;
}


