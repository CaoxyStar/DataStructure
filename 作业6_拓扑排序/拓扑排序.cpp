#include<iostream>
using namespace std;

struct Node {
	int idx = NULL;
	int indegree = INT16_MAX;
	Node* next = NULL;
};

int main()
{
	//基本信息输入并创建邻接表
	cout << "请输入顶点个数：";
	int n;
	cin >> n;
	cout << "（各顶点以1——" << n << "命名）" << endl;
	Node* node_list = new Node[n];
	for (int i = 0; i < n; i++)
	{
		node_list[i].idx = i;
		cout << "请输入顶点" << i + 1 << "的入度：";
		cin >> node_list[i].indegree;
		cout << "请输入顶点" << i + 1 << "的出度：";
		int temp;
		cin >> temp;
		if (temp > 0)
		{
			cout << "请输入顶点" << i + 1 << "的直接后继（以空格划分）：";
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

	int top = -1;	//栈顶指针
	int m = 0;		//记录输出元素个数

	//将入度为0的元素入度置为-1，为拓朴排序做准备
	for (int i = 0; i < n; i++)
		if (node_list[i].indegree == 0)
		{
			node_list[i].indegree = top;
			top = i;
		}

	//进行拓扑排序
	cout << "拓朴排序路径为：";
	while (top != -1)
	{
		int temp = top;
		top = node_list[top].indegree;
		cout << temp + 1;
		m++;
		Node* p = &node_list[temp];
		while (p->next != NULL)
		{
			//删除该以该顶点为起点的弧
			node_list[p->next->idx].indegree = node_list[p->next->idx].indegree - 1;
			//若删去弧后对应的终点入度变为0则加入栈
			if (node_list[p->next->idx].indegree == 0)
			{
				node_list[p->next->idx].indegree = top;
				top = p->next->idx;
			}
			p = p->next;
		}
	}
	cout << endl;
	//通过查看是否输出全部顶点判断该图是否有回路
	if (m < n)
	{
		cout << "未完成全图拓扑排序，此图有回路！" << endl;
		return -1;
	}
	system("pause");
	return 0;
}