#include<iostream>
#include<vector>
using namespace std;

//队列排程算法
vector<int> Sport_sort(int m, const vector<vector<int>>R)
{
	vector<int>cq(m);			//存储比赛各项目编号
	for (int i = 0; i < m; i++)
		cq[i] = i;
	vector<int>newr(m, 0);		//工作数组
	vector<int>Result(m, 0);	//存储各项目分组编号
	int front = m - 1;			//cq队列头指针
	int rear = m - 1;			//cq队列尾指针
	bool start = true;
	int pre = -1;				//记录上次处理的项目编号
	int group = 1;				//记录组号
	int I;

	//采用do-while的方法可以不用牺牲一个单元来判断队空
	do
	{
		front = (front + 1) % m;
		I = cq[front];
		if (I < pre)			//开辟新组并更新工作数组newr
		{
			group++;
			Result[I] = group;
			for (int i = 0; i < m; i++)
				newr[i] = R[I][i];
		}
		else
		{
			if (newr[I] != 0)		//被处理元素不可被选择
			{
				rear = (rear + 1) % m;
				cq[rear] = I;
			}
			else					//被处理元素可以被选择
			{
				Result[I] = group;
				for (int i = 0; i < m; i++)
					if (R[I][i] == 1)
						newr[i] = 1;
			}
		}
		pre = I;			//更新上次被处理元素的编号
	} while (rear != front);

	return Result;
}


int main()
{
	int n, m, k;
	cout << "请输入运动会比赛项目总个数：";
	cin >> n;
	vector<int>temp(n, 0);
	vector<vector<int>>R;
	for (int i = 0; i < n; i++)
		R.push_back(temp);
	cout << "***********************************" << endl;
	cout << n << "个比赛以1--" << n << "依次命名！" << endl;
	cout << "***********************************" << endl;
	cout << "请输入比赛中要参加两个及以上项目的运动员的个数（每人最多参加三个项目）：";
	cin >> m;

	//根据输入信息构建邻接矩阵
	for (int i = 0; i < m; i++)
	{
		int sporter[3];
		cout << "第" << i + 1 << "个运动员参加项目的个数：";
		cin >> k;
		if (k == 2)				//处理参加两个项目的运动员
		{
			cout << "项目a：";
			cin >> sporter[0];
			cout << "项目b：";
			cin >> sporter[1];
			R[sporter[0] - 1][sporter[1] - 1] = 1;
			R[sporter[1] - 1][sporter[0] - 1] = 1;
		}
		else if (k == 3)		//处理参加三个项目的远动员
		{
			cout << "项目a：";
			cin >> sporter[0];
			cout << "项目b：";
			cin >> sporter[1];
			cout << "项目c：";
			cin >> sporter[2];
			R[sporter[0] - 1][sporter[1] - 1] = 1;
			R[sporter[0] - 1][sporter[2] - 1] = 1;
			R[sporter[1] - 1][sporter[0] - 1] = 1;
			R[sporter[1] - 1][sporter[2] - 1] = 1;
			R[sporter[2] - 1][sporter[0] - 1] = 1;
			R[sporter[2] - 1][sporter[1] - 1] = 1;
		}
		else					//若超过三个项目，返回错误信息
		{
			cout << "错误，每个运动员至多参加三个项目！";
			system("pause");
			return 0;
		}
	}
	//根据邻接矩阵进行项目排列
	vector<int>sort_result = Sport_sort(n, R);

	//记录最大组号
	int group_num = 0;
	for (int i = 0; i < n; i++)
		if (sort_result[i] > group_num)
			group_num = sort_result[i];
	
	//打印分组信息
	for (int i = 1; i <= group_num; i++)
	{
		cout << "第" << i << "天安排的比赛项目为：";
		for (int j = 0; j < n; j++)
			if (sort_result[j] == i)
				cout << j+1 << ",";
		cout << endl;
	}

	system("pause");
	return 0;
}