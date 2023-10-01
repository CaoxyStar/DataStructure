#include<iostream>
#include<vector>
using namespace std;

//��̬�滮
void DP_Max(vector<vector<int>>& table, int* w, int* v, int n, int capacity)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= capacity; j++)
			if (j < w[i])		//��Ʒ�޷����뱳��
				table[i][j] = table[i - 1][j];
			else				//��Ʒ���Է��뱳��
				table[i][j] = max(table[i - 1][j], table[i - 1][j - w[i]] + v[i]); //������ѡ��
}

//���Ž��������ѡ��Ʒ
void Find_Object(vector<vector<int>> table, int* item, int* w, int n, int m)
{
	if (n > 0)
	{
		if (table[n][m] == table[n - 1][m])		//��Ʒδ��ѡ��
		{
			item[n] = 0;
			Find_Object(table, item, w, n - 1, m);
		}
		else		//��Ʒ��ѡ��
		{
			item[n] = 1;
			Find_Object(table, item, w, n - 1, m - w[n]);
		}
	}
}

//��ӡ
void Print(vector<vector<int>> table, int* item, int n)
{
	cout << "***��̬�滮��***" << endl;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j <= 8; j++)
			cout << table[i][j] << " ";
		cout << endl;
	}
	for (int i = 1; i <= n; i++)
		if (item[i] == 1)
			cout << "��" << i << "����Ʒ��ѡ��" << endl;
	cout << endl;
}


int main()
{
	int n, capacity;	//�洢��Ʒ�����뱳������
	cout << "***�������Ž�����***" << endl;
	cout << "��������Ʒ������";
	cin >> n;
	int* w = new int[n + 1];		//�洢����Ʒ����
	int* v = new int[n + 1];		//�洢����Ʒ��ֵ
	int* item = new int[n + 1];		//��¼��Ʒ�Ƿ�ѡ��
	w[0] = 0;
	v[0] = 0;

	//������Ʒ��Ϣ
	for (int i = 1; i <= n; i++)
	{
		cout << "�������" << i << "����Ʒ����Ϣ" << endl;
		cout << "�����";
		cin >> w[i];
		cout << "��ֵ��";
		cin >> v[i];
	}
	cout << "�����뱳�����������";
	cin >> capacity;

	//������̬�滮��
	vector<vector<int>>table;
	vector<int>temp(capacity + 1, 0);
	for (int i = 0; i <= n; i++)
		table.push_back(temp);

	//��̬�滮�����Ž�
	DP_Max(table, w, v, n, capacity);
	//���ݷ�ȷ����Ʒѡ��
	Find_Object(table, item, w, n, capacity);
	//��ӡ���
	Print(table, item, n);

	system("pause");
	return 0;
}