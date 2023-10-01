#include<iostream>
using namespace std;

struct Node {
	int idx = NULL;
	int indegree = INT16_MAX;
	Node* next = NULL;
};

int main()
{
	//������Ϣ���벢�����ڽӱ�
	cout << "�����붥�������";
	int n;
	cin >> n;
	cout << "����������1����" << n << "������" << endl;
	Node* node_list = new Node[n];
	for (int i = 0; i < n; i++)
	{
		node_list[i].idx = i;
		cout << "�����붥��" << i + 1 << "����ȣ�";
		cin >> node_list[i].indegree;
		cout << "�����붥��" << i + 1 << "�ĳ��ȣ�";
		int temp;
		cin >> temp;
		if (temp > 0)
		{
			cout << "�����붥��" << i + 1 << "��ֱ�Ӻ�̣��Կո񻮷֣���";
			Node* p = &node_list[i];
			for (int j = 0; j < temp; j++)
			{
				Node* node = new Node;
				cin >> node->idx;
				node->idx--;
				p->next = node;
				p = node;
			}
		}
		cout << "-----------------" << endl;
	}

	int top = -1;	//ջ��ָ��
	int m = 0;		//��¼���Ԫ�ظ���

	//�����Ϊ0��Ԫ�������Ϊ-1��Ϊ����������׼��
	for (int i = 0; i < n; i++)
		if (node_list[i].indegree == 0)
		{
			node_list[i].indegree = top;
			top = i;
		}

	//������������
	cout << "��������·��Ϊ��";
	while (top != -1)
	{
		int temp = top;
		top = node_list[top].indegree;
		cout << temp + 1;
		m++;
		Node* p = &node_list[temp];
		while (p->next != NULL)
		{
			//ɾ�����Ըö���Ϊ���Ļ�
			node_list[p->next->idx].indegree = node_list[p->next->idx].indegree - 1;
			//��ɾȥ�����Ӧ���յ���ȱ�Ϊ0�����ջ
			if (node_list[p->next->idx].indegree == 0)
			{
				node_list[p->next->idx].indegree = top;
				top = p->next->idx;
			}
			p = p->next;
		}
	}
	cout << endl;
	//ͨ���鿴�Ƿ����ȫ�������жϸ�ͼ�Ƿ��л�·
	if (m < n)
	{
		cout << "δ���ȫͼ�������򣬴�ͼ�л�·��" << endl;
		return -1;
	}
	system("pause");
	return 0;
}