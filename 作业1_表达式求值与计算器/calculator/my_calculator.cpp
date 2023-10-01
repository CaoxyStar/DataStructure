#include "my_calculator.h"
#include "iostream"
#include "math.h"
using namespace std;

//构成NS栈的节点
struct NS_node
{
    double number=0;
    NS_node* next=NULL;
};
//构成OS栈的节点
struct OS_node
{
    char symbol=';';
    OS_node *next=NULL;
};


double main_func(string str)
{
    	  NS_node* ns_top=new NS_node;
        OS_node* os_top=new OS_node;
	  
	  //如果一个个符号为符号则另外处理
        if(str[0]=='-')
        {
            os_top=OS_PUSH(os_top,'-');
            str=str.substr(1);
        }

        int start=0;	//记录每一个操作数的首位序号
        for(int i=0;i<str.length();i++)
        {
            if ((str[i]!='^')&&(str[i]!='x')&&(str[i]!='/')&&(str[i]!='+')&&(str[i]!='-')&&(str[i]!=';'))		//如果不是运算符跳过本次循环
                continue;
		//是运算符则首先压入其之前的操作数，再进行运算符的压入
            else
            {
		    //获取操作数
                ns_top=NS_PUSH(ns_top,stod(str.substr(start,i-start)));
                start=i+1;
			
		    //比较栈顶符号和当前符号优先级
                int pri_wait=Priority_Switch(str[i]);
                int pri_top=Priority_Switch(os_top->symbol);
		  //当前符号优先级不大于OS栈顶元素优先级弹出一个运算符和两个操作数
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
		   //当前符号优先级小于OS栈顶元素优先级直接压入
                os_top=OS_PUSH(os_top,str[i]);
            }
        }
	  //返回计算结果
        return ns_top->number;
}

//NS链表弹出元素
NS_node* NS_POP(NS_node* top,double* num)
{
    *num=top->number;
    NS_node* temp=top;
    top=temp->next;
    delete temp;
    return top;
}
//OS链表弹出元素
OS_node* OS_POP(OS_node* top,char* ch)
{
    *ch=top->symbol;
    OS_node* temp=top;
    top=top->next;
    delete temp;
    return top;
}
//NS链表压入元素
NS_node* NS_PUSH(NS_node* top,double x)
{
    NS_node* temp=new NS_node;
    temp->number=x;
    temp->next=top;
    return temp;
}
//OS链表压入元素
OS_node* OS_PUSH(OS_node* top,char ch)
{
    OS_node* temp=new OS_node;
    temp->symbol=ch;
    temp->next=top;
    return temp;
}

//运算符转优先级
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

//完成一次计算
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
