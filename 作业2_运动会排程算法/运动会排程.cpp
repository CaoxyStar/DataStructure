#include<iostream>
#include<vector>
using namespace std;

//�����ų��㷨
vector<int> Sport_sort(int m, const vector<vector<int>>R)
{
	vector<int>cq(m);			//�洢��������Ŀ���
	for (int i = 0; i < m; i++)
		cq[i] = i;
	vector<int>newr(m, 0);		//��������
	vector<int>Result(m, 0);	//�洢����Ŀ������
	int front = m - 1;			//cq����ͷָ��
	int rear = m - 1;			//cq����βָ��
	bool start = true;
	int pre = -1;				//��¼�ϴδ������Ŀ���
	int group = 1;				//��¼���
	int I;

	//����do-while�ķ������Բ�������һ����Ԫ���ж϶ӿ�
	do
	{
		front = (front + 1) % m;
		I = cq[front];
		if (I < pre)			//�������鲢���¹�������newr
		{
			group++;
			Result[I] = group;
			for (int i = 0; i < m; i++)
				newr[i] = R[I][i];
		}
		else
		{
			if (newr[I] != 0)		//������Ԫ�ز��ɱ�ѡ��
			{
				rear = (rear + 1) % m;
				cq[rear] = I;
			}
			else					//������Ԫ�ؿ��Ա�ѡ��
			{
				Result[I] = group;
				for (int i = 0; i < m; i++)
					if (R[I][i] == 1)
						newr[i] = 1;
			}
		}
		pre = I;			//�����ϴα�����Ԫ�صı��
	} while (rear != front);

	return Result;
}


int main()
{
	int n, m, k;
	cout << "�������˶��������Ŀ�ܸ�����";
	cin >> n;
	vector<int>temp(n, 0);
	vector<vector<int>>R;
	for (int i = 0; i < n; i++)
		R.push_back(temp);
	cout << "***********************************" << endl;
	cout << n << "��������1--" << n << "����������" << endl;
	cout << "***********************************" << endl;
	cout << "�����������Ҫ�μ�������������Ŀ���˶�Ա�ĸ�����ÿ�����μ�������Ŀ����";
	cin >> m;

	//����������Ϣ�����ڽӾ���
	for (int i = 0; i < m; i++)
	{
		int sporter[3];
		cout << "��" << i + 1 << "���˶�Ա�μ���Ŀ�ĸ�����";
		cin >> k;
		if (k == 2)				//����μ�������Ŀ���˶�Ա
		{
			cout << "��Ŀa��";
			cin >> sporter[0];
			cout << "��Ŀb��";
			cin >> sporter[1];
			R[sporter[0] - 1][sporter[1] - 1] = 1;
			R[sporter[1] - 1][sporter[0] - 1] = 1;
		}
		else if (k == 3)		//����μ�������Ŀ��Զ��Ա
		{
			cout << "��Ŀa��";
			cin >> sporter[0];
			cout << "��Ŀb��";
			cin >> sporter[1];
			cout << "��Ŀc��";
			cin >> sporter[2];
			R[sporter[0] - 1][sporter[1] - 1] = 1;
			R[sporter[0] - 1][sporter[2] - 1] = 1;
			R[sporter[1] - 1][sporter[0] - 1] = 1;
			R[sporter[1] - 1][sporter[2] - 1] = 1;
			R[sporter[2] - 1][sporter[0] - 1] = 1;
			R[sporter[2] - 1][sporter[1] - 1] = 1;
		}
		else					//������������Ŀ�����ش�����Ϣ
		{
			cout << "����ÿ���˶�Ա����μ�������Ŀ��";
			system("pause");
			return 0;
		}
	}
	//�����ڽӾ��������Ŀ����
	vector<int>sort_result = Sport_sort(n, R);

	//��¼������
	int group_num = 0;
	for (int i = 0; i < n; i++)
		if (sort_result[i] > group_num)
			group_num = sort_result[i];
	
	//��ӡ������Ϣ
	for (int i = 1; i <= group_num; i++)
	{
		cout << "��" << i << "�찲�ŵı�����ĿΪ��";
		for (int j = 0; j < n; j++)
			if (sort_result[j] == i)
				cout << j+1 << ",";
		cout << endl;
	}

	system("pause");
	return 0;
}