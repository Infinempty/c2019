#include"myhead.cpp"
//                ��������ò�Ʋ�����ͷָ�� ͷָ����ǵ�һ��Ԫ�ص�ָ�� 
node* make(node* head)
{
	int mid=0;
	node* p1,*p2;
	while(1)
	{
		cout<<"����������Ҫ¼������� ���븺������"<<endl;
		cin>>mid;
		if(head==NULL)
		{
			p2=p1=new node;
			head=p1;
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
	return head;
}
void print(node *head)
{
	int x=1;
	node* now=head;
	while(now!=NULL&&now->num>=0)
	{
		cout<<"��"<<x<<"���ڵ��ֵΪ"<<now->num<<endl;
		now=now->next;
		x++;
	}
}
int find(node* head,int find,int position)
{
	node* now=head;
	int x=0;
	for(int i=1;now->next!=NULL;i++)
	{
		if(now->num==5)
		{
			x++;
			if(x==position)return i;
		}
		else
		{
			now=now->next;
		}
	}
	return -1;
}
node* reverse(node *head)
{
	node* pre=head;
    node* top=pre;
    node* mid=pre->next,*after;
    while(mid!=NULL)
	{
        after=mid->next;
        mid->next=pre;
        pre=mid;
        mid=after;
    }
    top->next=NULL;
    head=pre; 
    return head;
}
