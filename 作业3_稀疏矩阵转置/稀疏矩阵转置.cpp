#include<iostream>
using namespace std;

int main()
{
	//依次表示非零元素个数、行数、列数
	int tu, m, n;

	cout << "----稀疏矩阵转置测试程序----" << endl;
	cout << "请输入一个稀疏矩阵：" << endl;
	cout << "矩阵行数：" << endl;
	cin >> m;
	cout << "矩阵列数：" << endl;
	cin >> n;
	cout << "非零元素个数：" << endl;
	cin >> tu;

	//初始化A矩阵
	double* value = new double[tu];
	int* row = new int[tu];
	int* rank = new int[tu];
	//初始化B矩阵
	double* B_value = new double[tu];
	int* B_row = new int[tu];
	int* B_rank = new int[tu];

	//输入A矩阵
	cout << "--请依次输入各元素的元素值、行号、列号，以空格分隔--" << endl;
	for (int i = 0; i < tu; i++)
	{
		cout << "第" << i + 1 << "个元素：";
		cin >> value[i];
		cin >> row[i];
		cin >> rank[i];
		row[i] = row[i] - 1;
		rank[i] = rank[i] - 1;
	}

	//设置列辅助向量
	int* POT = new int[n];	// 记录每一列非零元素的个数
	int* NUN = new int[n];	// 记录每一列第一个非零元素的在三元组中的索引
	for (int i = 0; i < n; i++)
		NUN[i] = 0;
	for (int i = 0; i < tu; i++)
		NUN[rank[i]] = NUN[rank[i]] + 1;
	POT[0] = 0;
	for (int i = 1; i < n; i++)
		POT[i] = POT[i - 1] + NUN[i - 1];

	//利用列辅助向量对A矩阵进行转置并将结果赋给B矩阵
	for (int i = 0; i < tu; i++)
	{
		int idx = POT[rank[i]];
		B_value[idx] = value[i];
		B_rank[idx] = row[i] + 1;
		B_row[idx] = rank[i] + 1;
		POT[rank[i]]++;
	}

	//打印转置结果
	cout << "----------------------------" << endl;
	cout << "转置后的矩阵三元组表示为：" << endl;
	cout << "row\trank\tvalue" << endl;
	for (int i = 0; i < tu; i++)
		cout << B_row[i] << "\t" << B_rank[i] << "\t" << B_value[i] << endl;

	system("pause");
	return 0;
}