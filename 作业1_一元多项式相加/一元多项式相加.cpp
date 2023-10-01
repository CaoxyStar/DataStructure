#include<iostream>
#include<string>
using namespace std;

//������洢����ʽ������ʽÿһ����Ϊһ��node�ڵ�
struct node
{
	int exp_value = NULL;		//ָ��
	int coef_value = NULL;		//ϵ��
	node* next = NULL;			//nextָ��
};

node* Add_poly(node* head1, node* head2)
{
	node* p = head1->next;
	node* q = head2->next;
	node* pre = head1;
	node* hc = head1;
	while (p != NULL && q != NULL)
	{
		if (p->exp_value < q->exp_value)		//p���ָ��С��q��ʱ��p����
		{
			pre = p;
			p = p->next;
		}
		else if (p->exp_value > q->exp_value)	//p��ָ������q��ʱ����q�����p��֮ǰ
		{
			node* u = q->next;
			q->next = p;
			pre->next = q;
			pre = q;
			q = u;
		}
		else									//p��ָ������q��ʱ
		{
			int sum = p->coef_value + q->coef_value;
			if (sum != 0)						//ϵ����ӺͲ�Ϊ0�����
			{
				p->coef_value = sum;
				pre = p;
			}
			else								//ϵ����Ӻ�Ϊ0�����
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
	//�������ʽB�����ǿգ�������ڶ���ʽA��
	if (q != NULL)
		pre->next = q;
	delete head2;

	return hc;
}


int main()
{
	int n1, n2;		//����ʽA��B������
	node* head1 = new node;		//����ʽA��ͷ�ڵ�
	node* tail_1 = head1;		//����ʽA��βָ��
	node* head2 = new node;		//����ʽB��ͷ�ڵ�
	node* tail_2 = head2;		//����ʽB��βָ��

	cout << "**********************" << endl;
	cout << "****һԪ����ʽ���****" << endl;
	cout << "**********************" << endl;

	//�������ʽA
	cout << "���������ʽA������:";
	cin >> n1;
	cout << "���������ʽA��" << endl;
	for (int i = 0; i < n1; i++)
	{
		node* next_node = new node;
		cout << "��" << i + 1 << "��ϵ����";
		cin >> next_node->coef_value;
		cout << "��" << i + 1 << "��ָ����";
		cin >> next_node->exp_value;
		tail_1->next = next_node;
		tail_1 = next_node;
	}

	//�������ʽB
	cout << "���������ʽB������:";
	cin >> n2;
	cout << "���������ʽB��" << endl;
	for (int i = 0; i < n2; i++)
	{
		node* next_node = new node;
		cout << "��" << i + 1 << "��ϵ����";
		cin >> next_node->coef_value;
		cout << "��" << i + 1 << "��ָ����";
		cin >> next_node->exp_value;
		tail_2->next = next_node;
		tail_2 = next_node;
	}

	//����ʽ���
	node* hc = Add_poly(head1, head2);

	//������
	cout << "**********************" << endl;
	cout << "��ʽ��ӽ��ΪLc=";
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