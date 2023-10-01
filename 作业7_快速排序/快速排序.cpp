#include<iostream>
using namespace std;

//���ο�������
void Qksort(int* list, int l, int h)
{
	//ǰ���жϣ�������������������
	if (l >= h)
		return;

	//ѡȡ���ƹؼ����Լ�������������ĩλ��
	int temp = list[l];
	int j = l;
	int k = h;

	//����
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

	//�ݹ��������б��������
	Qksort(list, l, j - 1);
	Qksort(list, j + 1, h);
	return;
}

int main()
{
	//����������б�
	cout << "����������������б��Ԫ�ظ�����";
	int n;
	cin >> n;
	cout << "�������б���Ԫ���Կո񻮷֣���";
	int* list = new int[n];
	for (int i = 0; i < n; i++)
		cin >> list[i];

	int temp = list[0];
	int j = 0;
	int k = n - 1;
	
	Qksort(list, j, k);
	
	//������
	cout << "��С��������������б�Ϊ��";
	for (int i = 0; i < n; i++)
		cout << list[i] << " ";
	cout << endl;

	system("pause");
	return 0;
}