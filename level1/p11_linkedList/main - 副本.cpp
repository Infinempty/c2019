#include<iostream>
#include<conio.h>
using namespace std;
struct node
{
	int num;
	node* next;
};
node* make(node* head);
int main(int data[],int n)
{
	node* header=NULL;
	int mid=0;
	node *p1,*p2;
	for(int i=0;i<n;i++)
	{
		mid=data[i];
		if(header==NULL)
		{
			p2=p1=new node;
			header=p1;
		}
		else
		{
			p1=new node;
		}
		if(mid<0)break;
		else p1->num=mid;
		p2->next=p1;
		p1->next=NULL;
		p2=p1;
	}
	return (int)header;
}

