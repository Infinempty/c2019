#include"myhead.cpp"
int main()
{
	int times=0;
	node* head=NULL;
	head=make(head);
	cout<<head->num;
	print(head);
	head=reverse(head);
	cout<<"�����Ѿ�����"<<endl;
	print(head);
	cout<<"����������Ҫ���ҵڼ���5"<<endl;
	cin>>times;
	if(find(head,5,times)!=-1)cout<<find(head,5,times);
	else cout<<"������û�е�"<<times<<"��5"<<endl; 
	return 0;
}
