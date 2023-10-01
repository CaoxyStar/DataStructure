#include<iostream>
#include<vector>
#include<string>
using namespace std;


int main()
{
	//输入邻接矩阵
	int n;
	cout << "请输入有向图中结点个数：";
	cin >> n;
	cout << "各结点以1——" << n << "命名！" << endl;
	vector<int>row(n);
	vector<vector<int>>chart;
	cout << "请按行输入有向图邻接矩阵，各元素以空格分隔：" << endl;
	cout << "(终点与起点相同时为0，终点与起点不同且连通时为边的权值，不连通时为-1)" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "第" << i + 1 << "行：";
		for (int j = 0; j < n; j++)
			cin >> row[j];
		chart.push_back(row);
	}

	//邻接矩阵调整，将不连通关系的权值由-1改为INT16_MAX
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (chart[i][j] == -1)
				chart[i][j] = INT16_MAX;

	//输入源点并进行辅助向量初始化
	cout << "请输入源点序号（各结点以1——" << n << "命名）：";
	int Start;
	cin >> Start;
	Start = Start - 1;
	
	bool* S = new bool[n];	//S为已找到最短路径的集合
	for (int i = 0; i < n; i++)
		S[i] = false;
	S[Start] = true;

	int* DIST = new int[n];	//DIST当前各节点最短路径的长度
	int* PATH = new int[n];	//PATH记录路径
	for (int i = 0; i < n; i++)
	{
		if (chart[Start][i] == INT16_MAX)
		{
			DIST[i] = INT16_MAX;
			PATH[i] = NULL;
		}
		else if (chart[Start][i] == 0)
		{
			DIST[i] = 0;
			PATH[i] = Start;
		}
		else
		{
			DIST[i] = chart[Start][i];
			PATH[i] = Start;
		}
	}

	//计算各节点最短路径
	for (int i = 0; i < n - 1; i++)
	{
		//在已找到最短路径结点之外，寻找当前路径最短的结点
		int min_num = INT32_MAX;
		int min_idx;
		for (int j = 0; j < n; j++)
		{
			if ((!(S[j])) && (DIST[j] < min_num))
			{
				min_num = DIST[j];
				min_idx = j;
			}
		}
		S[min_idx] = true;	//该节点当前路径即为最短路径，加入S列表

		//判断从min_idx结点出发能否找到其他结点相比当前更短的路径
		for (int j = 0; j < n; j++)
		{
			if (!(S[j]) && (DIST[min_idx] + chart[min_idx][j] < DIST[j]))
			{
				DIST[j] = DIST[min_idx] + chart[min_idx][j];
				PATH[j] = min_idx;
			}
		}
	}

	//打印结果
	for (int i = 0; i < n; i++)
	{
		cout << "结点" << i + 1 << "\t";
		if (PATH[i] != NULL)
		{
			cout << i + 1;
			int temp = PATH[i];
			while (temp != Start)
			{
				cout << "<-" << temp + 1;
				temp = PATH[temp];
			}
			cout << "<-" << Start + 1 << "\t" << DIST[i] << endl;
		}
		else
			cout << "nopath" << "\t" << "max" << endl;

	}
	system("pause");
	return 0;
}