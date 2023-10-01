#ifndef MY_CALCULATOR_H
#define MY_CALCULATOR_H

#include "string"

struct NS_node;
struct OS_node;

int Priority_Switch(char);
double Singe_calculate(double, double, char);
NS_node* NS_POP(NS_node*,double*);
NS_node* NS_PUSH(NS_node*,double);
OS_node* OS_POP(OS_node*,char*);
OS_node* OS_PUSH(OS_node*,char);
double main_func(std::string);


#endif // MY_CALCULATOR_H
