#include<iostream>
#include<vector>
using namespace std;

//动态规划
void DP_Max(vector<vector<int>>& table, int* w, int* v, int n, int capacity)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= capacity; j++)
			if (j < w[i])		//物品无法放入背包
				table[i][j] = table[i - 1][j];
			else				//物品可以放入背包
				table[i][j] = max(table[i - 1][j], table[i - 1][j - w[i]] + v[i]); //求最优选择
}

//最优解回溯求所选物品
void Find_Object(vector<vector<int>> table, int* item, int* w, int n, int m)
{
	if (n > 0)
	{
		if (table[n][m] == table[n - 1][m])		//物品未被选中
		{
			item[n] = 0;
			Find_Object(table, item, w, n - 1, m);
		}
		else		//物品被选中
		{
			item[n] = 1;
			Find_Object(table, item, w, n - 1, m - w[n]);
		}
	}
}

//打印
void Print(vector<vector<int>> table, int* item, int n)
{
	cout << "***动态规划表***" << endl;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 8; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	for (int i = 1; i <= n; i++)
		if (item[i] == 1)
			cout << "第" << i << "件物品被选择！" << endl;
	cout << endl;
}


int main()
{
	int n, capacity;	//存储物品个数与背包容量
	cout << "***背包最优解问题***" << endl;
	cout << "请输入物品个数：";
	cin >> n;
	int* w = new int[n + 1];		//存储各物品重量
	int* v = new int[n + 1];		//存储各物品价值
	int* item = new int[n + 1];		//记录物品是否被选择
	w[0] = 0;
	v[0] = 0;

	//输入物品信息
	for (int i = 1; i <= n; i++)
	{
		cout << "请输入第" << i << "件物品的信息" << endl;
		cout << "体积：";
		cin >> w[i];
		cout << "价值：";
		cin >> v[i];
	}
	cout << "请输入背包最大容量：";
	cin >> capacity;

	//创建动态规划表
	vector<vector<int>>table;
	vector<int>temp(capacity + 1, 0);
	for (int i = 0; i <= n; i++)
		table.push_back(temp);

	//动态规划求最优解
	DP_Max(table, w, v, n, capacity);
	//回溯法确定物品选择
	Find_Object(table, item, w, n, capacity);
	//打印结果
	Print(table, item, n);

	system("pause");
	return 0;
}