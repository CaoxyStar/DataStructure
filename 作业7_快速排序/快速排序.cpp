#include<iostream>
using namespace std;

//单次快速排序
void Qksort(int* list, int l, int h)
{
	//前置判断，若不满足则无需排序
	if (l >= h)
		return;

	//选取控制关键字以及待排序区间首末位置
	int temp = list[l];
	int j = l;
	int k = h;

	//排序
	while (j != k)
	{
		while ((j != k)&&(list[k] >= temp))
			k--;
		list[j] = list[k];

		while ((j != k)&&(list[j] <= temp))
			j++;
		list[k] = list[j];
	}
	list[j] = temp;

	//递归至整个列表完成排序
	Qksort(list, l, j - 1);
	Qksort(list, j + 1, h);
	return;
}

int main()
{
	//输入待排序列表
	cout << "请输入需进行排序列表的元素个数：";
	int n;
	cin >> n;
	cout << "请输入列表（各元素以空格划分）：";
	int* list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];

	int temp = list[0];
	int j = 0;
	int k = n - 1;
	
	Qksort(list, j, k);
	
	//结果输出
	cout << "有小到大快速排序后的列表为：";
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}