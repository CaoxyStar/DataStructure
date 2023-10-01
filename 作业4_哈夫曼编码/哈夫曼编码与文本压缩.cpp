#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;


int main()
{
	//读取文本
	ifstream fin;
	fin.open("D:\\大学\\编程\\c++\\数据结构\\哈夫曼编码与文本压缩\\book.txt");
	if (!fin.is_open())
	{
		cout << "Error opening file";
		return -1;
	}
	string txt, line;
	while (getline(fin, line))
		txt = txt + line;
	fin.close();
	cout << "文本已成功读取，正在分析......" << endl;


	//字符统计
	int txt_len = txt.length();	//文本长度
	vector<char> str;	//记录出现的字符
	vector<int> weight;	//记录字符出现次数

	for (int i = 0; i < txt_len; i++)
	{
		bool flag = false;	//标志当前字符是否出现过，false未出现，true已出现
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] == txt[i])
			{
				weight[j]++;
				flag = true;
				break;
			}
		}
		//当前字符未出现过则加入str并更新其weight为1
		if (!flag)
		{
			str.push_back(txt[i]);
			weight.push_back(1);
		}
	}
	cout << "文本已分析完毕，开始编码......" << endl;


	//静态向量初始化
	int char_len = str.size();	//不同字符的个数
	int* L_child = new int[2 * char_len - 1];	//记录结点左孩子索引
	int* R_child = new int[2 * char_len - 1];	//记录结点右孩子索引
	int* Parent = new int[2 * char_len - 1];	//记录结点双亲索引
	int* data = new int[2 * char_len - 1];		//记录结点权重大小
	string * code = new string[2 * char_len - 1];	//记录结点编码

	for (int i = 0; i < char_len; i++)
		data[i] = weight[i];

	for (int i = 0; i < 2 * char_len - 1; i++)
	{
		Parent[i] = -1;		//结点双亲置空
		L_child[i] = -1;	//结点左孩子置空
		R_child[i] = -1;	//结点右孩子置空
		code[i] = "";
	}

	//构建哈夫曼树
	for (int i = char_len; i < 2 * char_len - 1; i++)
	{
		int min_idx1;
		int min_idx2;
		int min_value1 = INT32_MAX;
		int min_value2 = INT32_MAX;

		//选取两个最小权重且无双亲的结点的索引
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

		//使左孩子权重小于右孩子，哈夫曼树更有条理
		if (min_value1 > min_value2)
		{
			int temp = min_idx1;
			min_idx1 = min_idx2;
			min_idx2 = temp;
		}

		//建立双亲与孩子的联系
		data[i] = min_value1 + min_value2;
		L_child[i] = min_idx1;
		R_child[i] = min_idx2;
		Parent[min_idx1] = i;
		Parent[min_idx2] = i;
	}
	
	//根据哈夫曼树对各字符进行编码，采用栈的方式，不使用常见的递归方式
	const string left_code = "0";
	const string right_code = "1";
	int* inn = new int[char_len];	//构造栈存放待处理结点
	inn[0] = 2 * char_len - 2;
	int pot = 1;		//栈顶指针
	
	//栈非空则执行循环
	while (pot != 0)
	{
		pot = pot - 1;
		int node = inn[pot];

		//栈顶元素有孩子则对孩子进行编码将孩子压入栈，右先左后
		if ((L_child[node] != -1) && (R_child[node] != -1))
		{
			code[L_child[node]] = code[node] + left_code;
			code[R_child[inn[pot]]] = code[node] + right_code;
			inn[pot] = R_child[node];
			inn[pot + 1] = L_child[node];
			pot = pot + 2;
		}
	}

	//编码结果保存到文件Dict.txt
	ofstream dict_out("D:\\大学\\编程\\c++\\数据结构\\哈夫曼编码与文本压缩\\Dict.txt");
	cout << "---------------------------------------------------------------------------------" << endl;
	dict_out << "编码结果（ -1代表该结点无孩子或双亲 ）" << endl;
	dict_out << "字符\t权重\t双亲\t左孩子\t右孩子\t编码" << endl;
	for (int i = 0; i < 2 * char_len - 1; i++)
	{
		if (i < char_len)
			dict_out << str[i] << "\t";
		else
			dict_out << " \t";
		dict_out << data[i] << "\t" << Parent[i] << "\t" << L_child[i] << "\t" << R_child[i] << "\t" << code[i] << endl;
	}
	cout << "编码结果已保存到文件Dict.txt" << endl;

	//对文本进行压缩并以二进制数保存到文件 "book_compress.txt"，该方式由于将二进制数以字节形式保存反而使文本变大
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "开始根据编码压缩文本......" << endl;
	ofstream fout1("D:\\大学\\编程\\c++\\数据结构\\哈夫曼编码与文本压缩\\book_compress_binary.txt");
	if (fout1.is_open())
	{
		for (int i = 0; i < txt_len; i++)
			for (int j = 0; j < char_len; j++)
				if (txt[i] == str[j])
					fout1 << code[j];
		cout << "二进制编码保存到book_compress_binary.txt" << endl;
	}
	else
		cout << "保存压缩文件失败！" << endl;
	fout1.close();


	//将8位二进制数转化为ASCII码进行保存，这样可以有效压缩文件，但是由于部分ASCII码无法打印故出现乱码
	ofstream fout2("D:\\大学\\编程\\c++\\数据结构\\哈夫曼编码与文本压缩\\book_compress_ASCII.txt");
	string out="";
	for (int i = 0; i < txt_len; i++)
	{
		for (int j = 0; j < char_len; j++)
			if (txt[i] == str[j])
				out = out + code[j];

		// 当二进制编码长度为8的整数倍时进行转化，每8位转化为一个ASCII码保存，并将out清空
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

	// 如果最后存在因不是8的整数倍而尚未被处理的字符，将最后多余的几位补成八位进行转化
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
	cout << "ASCII编码保存到book_compress_ASCII.txt" << endl;
	fout2.close();
	cout << "压缩完毕！" << endl;

	std::system("pause");
	return 0;
}