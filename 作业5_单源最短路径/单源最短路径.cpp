#include<iostream>
#include<vector>
#include<string>
using namespace std;


int main()
{
	//�����ڽӾ���
	int n;
	cout << "����������ͼ�н�������";
	cin >> n;
	cout << "�������1����" << n << "������" << endl;
	vector<int>row(n);
	vector<vector<int>>chart;
	cout << "�밴����������ͼ�ڽӾ��󣬸�Ԫ���Կո�ָ���" << endl;
	cout << "(�յ��������ͬʱΪ0���յ�����㲻ͬ����ͨʱΪ�ߵ�Ȩֵ������ͨʱΪ-1)" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "��" << i + 1 << "�У�";
		for (int j = 0; j < n; j++)
			cin >> row[j];
		chart.push_back(row);
	}

	//�ڽӾ��������������ͨ��ϵ��Ȩֵ��-1��ΪINT16_MAX
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (chart[i][j] == -1)
				chart[i][j] = INT16_MAX;

	//����Դ�㲢���и���������ʼ��
	cout << "������Դ����ţ��������1����" << n << "��������";
	int Start;
	cin >> Start;
	Start = Start - 1;
	
	bool* S = new bool[n];	//SΪ���ҵ����·���ļ���
	for (int i = 0; i < n; i++)
		S[i] = false;
	S[Start] = true;

	int* DIST = new int[n];	//DIST��ǰ���ڵ����·���ĳ���
	int* PATH = new int[n];	//PATH��¼·��
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

	//������ڵ����·��
	for (int i = 0; i < n - 1; i++)
	{
		//�����ҵ����·�����֮�⣬Ѱ�ҵ�ǰ·����̵Ľ��
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
		S[min_idx] = true;	//�ýڵ㵱ǰ·����Ϊ���·��������S�б�

		//�жϴ�min_idx�������ܷ��ҵ����������ȵ�ǰ���̵�·��
		for (int j = 0; j < n; j++)
		{
			if (!(S[j]) && (DIST[min_idx] + chart[min_idx][j] < DIST[j]))
			{
				DIST[j] = DIST[min_idx] + chart[min_idx][j];
				PATH[j] = min_idx;
			}
		}
	}

	//��ӡ���
	for (int i = 0; i < n; i++)
	{
		cout << "���" << i + 1 << "\t";
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