#include<iostream>
using namespace std;

int main()
{
	//���α�ʾ����Ԫ�ظ���������������
	int tu, m, n;

	cout << "----ϡ�����ת�ò��Գ���----" << endl;
	cout << "������һ��ϡ�����" << endl;
	cout << "����������" << endl;
	cin >> m;
	cout << "����������" << endl;
	cin >> n;
	cout << "����Ԫ�ظ�����" << endl;
	cin >> tu;

	//��ʼ��A����
	double* value = new double[tu];
	int* row = new int[tu];
	int* rank = new int[tu];
	//��ʼ��B����
	double* B_value = new double[tu];
	int* B_row = new int[tu];
	int* B_rank = new int[tu];

	//����A����
	cout << "--�����������Ԫ�ص�Ԫ��ֵ���кš��кţ��Կո�ָ�--" << endl;
	for (int i = 0; i < tu; i++)
	{
		cout << "��" << i + 1 << "��Ԫ�أ�";
		cin >> value[i];
		cin >> row[i];
		cin >> rank[i];
		row[i] = row[i] - 1;
		rank[i] = rank[i] - 1;
	}

	//�����и�������
	int* POT = new int[n];	// ��¼ÿһ�з���Ԫ�صĸ���
	int* NUN = new int[n];	// ��¼ÿһ�е�һ������Ԫ�ص�����Ԫ���е�����
	for (int i = 0; i < n; i++)
		NUN[i] = 0;
	for (int i = 0; i < tu; i++)
		NUN[rank[i]] = NUN[rank[i]] + 1;
	POT[0] = 0;
	for (int i = 1; i < n; i++)
		POT[i] = POT[i - 1] + NUN[i - 1];

	//�����и���������A�������ת�ò����������B����
	for (int i = 0; i < tu; i++)
	{
		int idx = POT[rank[i]];
		B_value[idx] = value[i];
		B_rank[idx] = row[i] + 1;
		B_row[idx] = rank[i] + 1;
		POT[rank[i]]++;
	}

	//��ӡת�ý��
	cout << "----------------------------" << endl;
	cout << "ת�ú�ľ�����Ԫ���ʾΪ��" << endl;
	cout << "row\trank\tvalue" << endl;
	for (int i = 0; i < tu; i++)
		cout << B_row[i] << "\t" << B_rank[i] << "\t" << B_value[i] << endl;

	system("pause");
	return 0;
}