#include"myhead.h"
int scan()
{
	int i = 1;
	for (;; i++)
	{
		cin >> good[i].order;
		if (good[i].order == 0)break;
		cin >> good[i].name >> good[i].num;
	}
	return i - 1;
}
void print()
{
	cout<<"���ڲֿ����������¿��"<<endl;
	for (int i = 1;; i++)
	{
		if (good[i].order == 0)break;
		else if (good[i].order == 2)continue;
		cout << i << " " << good[i].name << " " << good[i].num << endl;
	}
	cout << "�����Ҫ�������������1 ��Ҫ��������Ŀ������2 ��Ҫɾ����Ŀ������3 �˳�������4"<<endl;
}
void save()
{
	for (int i = 1;good[i].order!=0; i++)
	{
		if (good[i].order == 2)continue;
		cout << good[i].order << " " << good[i].name << " " << good[i].num << endl;
	}
	cout << 0;
}
void in()
{
	int x = 0, nums = 0, times = 0, in_out = 0;;
	cout << "����2���� ����1���" << endl;
	cin >> times;
	if (times == 2)in_out = -1;
	else in_out == 1;
	cout << "����������Ҫ��/������Ʒ�����" << endl;
	cin >> x;
	cout << "����������Ҫ��/������Ʒ������" << endl;
	cin >> nums;
	good[x].num += (nums*in_out);
}
int create(int all)
{
	good[all + 1].order = 1;
	cout << "���������Ʒ����" << endl;
	cin >> good[all + 1].name;
	cout << "����������" << endl;
	cin >> good[all + 1].num;
	cout << "�������" << endl;
	return all + 1;
}
int my_remove(int all)
{
	int x = 0;
	cout << "���������Ʒ�����" << endl;
	cin >> x;
	good[x].order = 0;
	return all - 1;
}