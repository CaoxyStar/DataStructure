#include "my_calculator.h"
#include "iostream"
#include "math.h"
using namespace std;

//����NSջ�Ľڵ�
struct NS_node
{
    double number=0;
    NS_node* next=NULL;
};
//����OSջ�Ľڵ�
struct OS_node
{
    char symbol=';';
    OS_node *next=NULL;
};


double main_func(string str)
{
    	  NS_node* ns_top=new NS_node;
        OS_node* os_top=new OS_node;
	  
	  //���һ��������Ϊ���������⴦��
        if(str[0]=='-')
        {
            os_top=OS_PUSH(os_top,'-');
            str=str.substr(1);
        }

        int start=0;	//��¼ÿһ������������λ���
        for(int i=0;i<str.length();i++)
        {
            if ((str[i]!='^')&&(str[i]!='x')&&(str[i]!='/')&&(str[i]!='+')&&(str[i]!='-')&&(str[i]!=';'))		//��������������������ѭ��
                continue;
		//�������������ѹ����֮ǰ�Ĳ��������ٽ����������ѹ��
            else
            {
		    //��ȡ������
                ns_top=NS_PUSH(ns_top,stod(str.substr(start,i-start)));
                start=i+1;
			
		    //�Ƚ�ջ�����ź͵�ǰ�������ȼ�
                int pri_wait=Priority_Switch(str[i]);
                int pri_top=Priority_Switch(os_top->symbol);
		  //��ǰ�������ȼ�������OSջ��Ԫ�����ȼ�����һ�������������������
                while ((!(pri_wait>pri_top))&&(!((pri_wait==0)&&(pri_top==0))))
                {
                    double num1,num2;
                    ns_top=NS_POP(ns_top,&num1);
                    ns_top=NS_POP(ns_top,&num2);
                    char ch;
                    os_top=OS_POP(os_top,&ch);

                    pri_top=Priority_Switch(os_top->symbol);

                    double num=Singe_calculate(num1,num2,ch);
                    ns_top=NS_PUSH(ns_top,num);
                }
		   //��ǰ�������ȼ�С��OSջ��Ԫ�����ȼ�ֱ��ѹ��
                os_top=OS_PUSH(os_top,str[i]);
            }
        }
	  //���ؼ�����
        return ns_top->number;
}

//NS������Ԫ��
NS_node* NS_POP(NS_node* top,double* num)
{
    *num=top->number;
    NS_node* temp=top;
    top=temp->next;
    delete temp;
    return top;
}
//OS������Ԫ��
OS_node* OS_POP(OS_node* top,char* ch)
{
    *ch=top->symbol;
    OS_node* temp=top;
    top=top->next;
    delete temp;
    return top;
}
//NS����ѹ��Ԫ��
NS_node* NS_PUSH(NS_node* top,double x)
{
    NS_node* temp=new NS_node;
    temp->number=x;
    temp->next=top;
    return temp;
}
//OS����ѹ��Ԫ��
OS_node* OS_PUSH(OS_node* top,char ch)
{
    OS_node* temp=new OS_node;
    temp->symbol=ch;
    temp->next=top;
    return temp;
}

//�����ת���ȼ�
int Priority_Switch(char ch)
{
    int res;
    if(ch==';')
        res=0;
    else if((ch=='+')||(ch=='-'))
        res=1;
    else if((ch=='x')||(ch=='/'))
        res=2;
    else
        res=3;
    return res;
}

//���һ�μ���
double Singe_calculate(double num1,double num2,char ch)
{
    double res;
    switch(ch)
    {
        case '+':
            res=num1+num2;
            break;
        case '-':
            res=num2-num1;
            break;
        case 'x':
            res=num1*num2;
            break;
        case '/':
            res=num2/num1;
            break;
        case '^':
            res=pow(num2,num1);
            break;
    }
    return res;
}
