#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;


int main()
{
	//��ȡ�ı�
	ifstream fin;
	fin.open("D:\\��ѧ\\���\\c++\\���ݽṹ\\�������������ı�ѹ��\\book.txt");
	if (!fin.is_open())
	{
		cout << "Error opening file";
		return -1;
	}
	string txt, line;
	while (getline(fin, line))
		txt = txt + line;
	fin.close();
	cout << "�ı��ѳɹ���ȡ�����ڷ���......" << endl;


	//�ַ�ͳ��
	int txt_len = txt.length();	//�ı�����
	vector<char> str;	//��¼���ֵ��ַ�
	vector<int> weight;	//��¼�ַ����ִ���

	for (int i = 0; i < txt_len; i++)
	{
		bool flag = false;	//��־��ǰ�ַ��Ƿ���ֹ���falseδ���֣�true�ѳ���
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == txt[i])
			{
				weight[j]++;
				flag = true;
				break;
			}
		}
		//��ǰ�ַ�δ���ֹ������str��������weightΪ1
		if (!flag)
		{
			str.push_back(txt[i]);
			weight.push_back(1);
		}
	}
	cout << "�ı��ѷ�����ϣ���ʼ����......" << endl;


	//��̬������ʼ��
	int char_len = str.size();	//��ͬ�ַ��ĸ���
	int* L_child = new int[2 * char_len - 1];	//��¼�����������
	int* R_child = new int[2 * char_len - 1];	//��¼����Һ�������
	int* Parent = new int[2 * char_len - 1];	//��¼���˫������
	int* data = new int[2 * char_len - 1];		//��¼���Ȩ�ش�С
	string * code = new string[2 * char_len - 1];	//��¼������

	for (int i = 0; i < char_len; i++)
		data[i] = weight[i];

	for (int i = 0; i < 2 * char_len - 1; i++)
	{
		Parent[i] = -1;		//���˫���ÿ�
		L_child[i] = -1;	//��������ÿ�
		R_child[i] = -1;	//����Һ����ÿ�
		code[i] = "";
	}

	//������������
	for (int i = char_len; i < 2 * char_len - 1; i++)
	{
		int min_idx1;
		int min_idx2;
		int min_value1 = INT32_MAX;
		int min_value2 = INT32_MAX;

		//ѡȡ������СȨ������˫�׵Ľ�������
		for (int j = 0; j < i; j++)
		{
			if (((data[j] < min_value1) || (data[j] < min_value2)) && (Parent[j] == -1))
			{
				if (min_value1 >= min_value2)
				{
					min_value1 = data[j];
					min_idx1 = j;
				}
				else
				{
					min_value2 = data[j];
					min_idx2 = j;
				}
			}
		}

		//ʹ����Ȩ��С���Һ��ӣ�����������������
		if (min_value1 > min_value2)
		{
			int temp = min_idx1;
			min_idx1 = min_idx2;
			min_idx2 = temp;
		}

		//����˫���뺢�ӵ���ϵ
		data[i] = min_value1 + min_value2;
		L_child[i] = min_idx1;
		R_child[i] = min_idx2;
		Parent[min_idx1] = i;
		Parent[min_idx2] = i;
	}
	
	//���ݹ��������Ը��ַ����б��룬����ջ�ķ�ʽ����ʹ�ó����ĵݹ鷽ʽ
	const string left_code = "0";
	const string right_code = "1";
	int* inn = new int[char_len];	//����ջ��Ŵ�������
	inn[0] = 2 * char_len - 2;
	int pot = 1;		//ջ��ָ��
	
	//ջ�ǿ���ִ��ѭ��
	while (pot != 0)
	{
		pot = pot - 1;
		int node = inn[pot];

		//ջ��Ԫ���к�����Ժ��ӽ��б��뽫����ѹ��ջ���������
		if ((L_child[node] != -1) && (R_child[node] != -1))
		{
			code[L_child[node]] = code[node] + left_code;
			code[R_child[inn[pot]]] = code[node] + right_code;
			inn[pot] = R_child[node];
			inn[pot + 1] = L_child[node];
			pot = pot + 2;
		}
	}

	//���������浽�ļ�Dict.txt
	ofstream dict_out("D:\\��ѧ\\���\\c++\\���ݽṹ\\�������������ı�ѹ��\\Dict.txt");
	cout << "---------------------------------------------------------------------------------" << endl;
	dict_out << "�������� -1����ý���޺��ӻ�˫�� ��" << endl;
	dict_out << "�ַ�\tȨ��\t˫��\t����\t�Һ���\t����" << endl;
	for (int i = 0; i < 2 * char_len - 1; i++)
	{
		if (i < char_len)
			dict_out << str[i] << "\t";
		else
			dict_out << " \t";
		dict_out << data[i] << "\t" << Parent[i] << "\t" << L_child[i] << "\t" << R_child[i] << "\t" << code[i] << endl;
	}
	cout << "�������ѱ��浽�ļ�Dict.txt" << endl;

	//���ı�����ѹ�����Զ����������浽�ļ� "book_compress.txt"���÷�ʽ���ڽ������������ֽ���ʽ���淴��ʹ�ı����
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "��ʼ���ݱ���ѹ���ı�......" << endl;
	ofstream fout1("D:\\��ѧ\\���\\c++\\���ݽṹ\\�������������ı�ѹ��\\book_compress_binary.txt");
	if (fout1.is_open())
	{
		for (int i = 0; i < txt_len; i++)
			for (int j = 0; j < char_len; j++)
				if (txt[i] == str[j])
					fout1 << code[j];
		cout << "�����Ʊ��뱣�浽book_compress_binary.txt" << endl;
	}
	else
		cout << "����ѹ���ļ�ʧ�ܣ�" << endl;
	fout1.close();


	//��8λ��������ת��ΪASCII����б��棬����������Чѹ���ļ����������ڲ���ASCII���޷���ӡ�ʳ�������
	ofstream fout2("D:\\��ѧ\\���\\c++\\���ݽṹ\\�������������ı�ѹ��\\book_compress_ASCII.txt");
	string out="";
	for (int i = 0; i < txt_len; i++)
	{
		for (int j = 0; j < char_len; j++)
			if (txt[i] == str[j])
				out = out + code[j];

		// �������Ʊ��볤��Ϊ8��������ʱ����ת����ÿ8λת��Ϊһ��ASCII�뱣�棬����out���
		if (out.size() % 8 == 0)
		{
			int epoch = out.size() / 8;
			for (int k = 0; k < epoch; k++)
			{
				int sum = 0;
				for (int p = 7; p >= 0; p--)
					if (out[p] == '1')
						sum += pow(2, p);
				char letter = sum;
				fout2 << letter;
				if(!out.empty())
					out = out.substr(8);
			}
		}
	}

	// �������������8������������δ��������ַ�����������ļ�λ���ɰ�λ����ת��
	while (!out.empty())
	{
		if (out.size() > 8)
		{
			int sum = 0;
			for (int i = 7; i >= 0; i--)
				if (out[i] == '1')
					sum += pow(2, i);
			char letter = sum;
			fout2 << letter;
			out = out.substr(8);
		}
		else
		{
			int sum = 0;
			int p = out.size();
			for (int i = p-1; i >= 0; i--)
				if (out[i] == '1')
					sum += pow(2, i);
			char letter = sum;
			fout2 << letter;
			out = "";
		}
	}
	cout << "ASCII���뱣�浽book_compress_ASCII.txt" << endl;
	fout2.close();
	cout << "ѹ����ϣ�" << endl;

	std::system("pause");
	return 0;
}