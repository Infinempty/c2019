#include"myhead.h"
int scan()
{
	ifstream infile("data.txt");
	int i = 1;
	for (;infile!=NULL;i++)
	{
		infile >> good[i].order;
		infile >> good[i].name >> good[i].num;
	}
	infile.close();
	return i - 1;
}
void my_print(int all)
{
	cout<<"���ڲֿ����������¿��"<<endl;
	for (int i = 1;i<=all; i++)
	{
		if (good[i].order == 0)break;
		else if (good[i].order == 2)continue;
		cout << i << " " << good[i].name << " " << good[i].num <<"��"<< endl;
	}
	cout << "�����Ҫ�������������1 ��Ҫ��������Ŀ������2 ��Ҫɾ����Ŀ������3 �˳�������4"<<endl;
	cout<<"�˳�ʱ������4�˳� ����ᵼ�����ݶ�ʧ"<<endl;
}
void save(int all)
{
	ofstream outfile("data.txt");
	for (int i = 1;i<=all; i++)
	{
		if (good[i].order == 2)continue;
		outfile << good[i].order << " " << good[i].name << " " << good[i].num << endl;
	}
	outfile.close();
}
void in()
{
	int x = 0, nums = 0, times = 0, in_out = 0;;
	cout << "����1��� ����2����" << endl;
	cin >> times;
	if (times == 2)in_out = -1;
	else in_out = 1;
	cout << "����������Ҫ��/������Ʒ�����" << endl;
	cin >> x;
	cout << "����������Ҫ��/������Ʒ������" << endl;
	cin >> nums;
	good[x].num += (nums*in_out);
}
int create(int all)
{
	good[all].order = 1;
	cout << "���������Ʒ����" << endl;
	cin >> good[all].name;
	cout << "����������" << endl;
	cin >> good[all].num;
	cout << "�������" << endl;
	cout<<all<<endl;
	cout<<good[all].name<<" "<<good[all].num<<endl;
	return all + 1;
}
int my_remove(int all)
{
	int x = 0;
	cout << "���������Ʒ�����" << endl;
	cin >> x;
	good[x].order = 2;
	return all - 1;
}
