#include<iostream>
#include<string>
using namespace std;

//以链表存储多项式，多项式每一项视为一个node节点
struct node
{
	int exp_value = NULL;		//指数
	int coef_value = NULL;		//系数
	node* next = NULL;			//next指针
};

node* Add_poly(node* head1, node* head2)
{
	node* p = head1->next;
	node* q = head2->next;
	node* pre = head1;
	node* hc = head1;
	while (p != NULL && q != NULL)
	{
		if (p->exp_value < q->exp_value)		//p项的指数小于q项时，p后移
		{
			pre = p;
			p = p->next;
		}
		else if (p->exp_value > q->exp_value)	//p项指数大与q项时，将q项插入p项之前
		{
			node* u = q->next;
			q->next = p;
			pre->next = q;
			pre = q;
			q = u;
		}
		else									//p项指数等于q项时
		{
			int sum = p->coef_value + q->coef_value;
			if (sum != 0)						//系数相加和不为0的情况
			{
				p->coef_value = sum;
				pre = p;
			}
			else								//系数相加和为0的情况
			{
				pre->next = p->next;
				delete p;
			}
			p = pre->next;
			node* u = q;
			q = q->next;
			delete u;
		}
	}
	//如果多项式B余链非空，将其接在多项式A后
	if (q != NULL)
		pre->next = q;
	delete head2;

	return hc;
}


int main()
{
	int n1, n2;		//多项式A、B的项数
	node* head1 = new node;		//多项式A的头节点
	node* tail_1 = head1;		//多项式A的尾指针
	node* head2 = new node;		//多项式B的头节点
	node* tail_2 = head2;		//多项式B的尾指针

	cout << "**********************" << endl;
	cout << "****一元多项式相加****" << endl;
	cout << "**********************" << endl;

	//输入多项式A
	cout << "请输入多项式A的项数:";
	cin >> n1;
	cout << "请输入多项式A：" << endl;
	for (int i = 0; i < n1; i++)
	{
		node* next_node = new node;
		cout << "第" << i + 1 << "项系数：";
		cin >> next_node->coef_value;
		cout << "第" << i + 1 << "项指数：";
		cin >> next_node->exp_value;
		tail_1->next = next_node;
		tail_1 = next_node;
	}

	//输入多项式B
	cout << "请输入多项式B的项数:";
	cin >> n2;
	cout << "请输入多项式B：" << endl;
	for (int i = 0; i < n2; i++)
	{
		node* next_node = new node;
		cout << "第" << i + 1 << "项系数：";
		cin >> next_node->coef_value;
		cout << "第" << i + 1 << "项指数：";
		cin >> next_node->exp_value;
		tail_2->next = next_node;
		tail_2 = next_node;
	}

	//多项式相加
	node* hc = Add_poly(head1, head2);

	//结果输出
	cout << "**********************" << endl;
	cout << "两式相加结果为Lc=";
	node* k = hc->next;
	cout << k->coef_value << "X^" << k->exp_value;
	while (k->next != NULL)
	{
		if (k->next->coef_value > 0)
			cout << "+";
		cout << k->next->coef_value << "X^" << k->next->exp_value;
		k = k->next;
	}
	cout << endl << "**********************" << endl;

	system("pause");
	return 0;
}