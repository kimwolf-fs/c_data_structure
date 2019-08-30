#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

char opetr_char[7]={'+','-','*','/','%','(',')'};

//operational character priority (a,b),operational character b after a.
//   b: +  -  *  /  %  (  )
// a:
// +    >  >  <  <  <  <  >
// -    >  >  <  <  <  <  >
// *    >  >  >  >  >  <  >
// /    >  >  >  >  >  <  >
// %    >  >  >  >  >  <  >
// (    <  <  <  <  <  <  =
// )    >  >  >  >  >  N  N

char opetr_priority[7][7]={
	{'>','>','<','<','<','<','>'},
	{'>','>','<','<','<','<','>'},
	{'>','>','>','>','>','<','>'},
	{'>','>','>','>','>','<','>'},
	{'>','>','>','>','>','<','>'},
	{'<','<','<','<','<','<','='},
	{'>','>','>','>','>','N','N'}
};

int isOpetrChar(char ch){
	int i;
	for(i=0;i<7;i++){
		if(ch ==  opetr_char[i]) return i;
	}
	return -1;
}

char getOpetrPrior(char a,char b){
	int i = isOpetrChar(a);
	int j = isOpetrChar(b);
	return opetr_priority[i][j];
}

double my_pow(double a,int b){
	int s = 0,i;
	double r = 1;
	if(b == 0) return 1;
	if(b<0){
		b*=-1;
		s = 1;
	}
	for(i = 0; i < b; i++){
		r *= a;
	}
	if(s) r = 1/r;
	return r;
}

int getOpndNumFromStack(LinearListStack *opnd_stack){
	int num = 0,i = 0;
	char elem;
	if(opnd_stack->length(opnd_stack)){
		opnd_stack->pop(opnd_stack,&elem);
		if(elem == ' '){
			while(elem == ' '){
				if(opnd_stack->length(opnd_stack) == 0) break;//确保不会pop空栈
				opnd_stack->pop(opnd_stack,&elem);
			}
		}
		if(elem != ' '){ //两个判断必须分开来写
			while(elem != ' ' && elem != '-'){
				num += my_pow(10,i)*(elem - 0x30);
				if(opnd_stack->length(opnd_stack) == 0) break; //确保不会pop空栈
				opnd_stack->pop(opnd_stack,&elem);
				i++;
			}
			if(elem == '-'){ //如果是负号
				num = -num;
			}else if(elem == ' '){  //将移出的空格间隔符再补进去
				opnd_stack->push(opnd_stack,&elem);
			}
		}
	}
	return num;
}

int operate(int number_a,char opetr_char,int number_b){
	int result = 0;
	switch(opetr_char){
		case '+':
			result = number_a + number_b;
			break;
		case '-':
			result = number_a - number_b;
			break;
		case '*':
			result = number_a * number_b;
			break;
		case '/':
			result = number_a / number_b;
			break;
		case '%':
			result = number_a % number_b;
			break;
		default:
			result = number_b;
			break;
	}
	return result;
}

void pushResultToStack(LinearListStack *opnd_stack, int result){
	char elem[10],n_elem;
	int i = 0,index = 0;
	if(result < 0){
		result = - result;
		n_elem = '-';
		opnd_stack->push(opnd_stack,&n_elem);
	}else if(result == 0){
		n_elem = '0';
		opnd_stack->push(opnd_stack,&n_elem);
	}
	while(result > 0){
		elem[index] = (result % 10) + 0x30;
		result /= 10;
		index++;
	}
	for(i=index;i>0;i--){
		opnd_stack->push(opnd_stack,&elem[i-1]);
	}
}

LinearListStack *evaluateExpression(char *str){
	char elem,opetr_prior,opetr_char;
	int cal_result = 0,number_a,number_b;
	int num_before_flag = 0;
	LinearListStack *optr_stack = InitLinearListStack(); //运算符栈
	LinearListStack *opnd_stack = InitLinearListStack(); //操作数栈
	while(*str != '\0'){
		if(isOpetrChar(*str) != -1){
			if(optr_stack->length(optr_stack)){
				optr_stack->getTop(optr_stack,&elem);
				opetr_prior = getOpetrPrior(elem,*str);
				switch(opetr_prior){
					case '<': //栈顶运算符优先级低
						if(num_before_flag == 0){ //前一个入栈的是符号
							if(*str == '-'){ //此时'-'号表示为负号
								opnd_stack->push(opnd_stack,str);//'-'号加入操作数栈
								num_before_flag = 1; //加入的是数字
							}else if(elem == '(' || *str == '('){ //多个括号与操作符相邻的情况
								optr_stack->push(optr_stack,str);  
								elem = ' '; //数字字符加入空格间隔符
								opnd_stack->push(opnd_stack,&elem);
								num_before_flag = 0;//加入运算符
							}else{
								printf("Expression format error!");
								break;
							}
						}else{ //前面有数字入栈
							optr_stack->push(optr_stack,str);  
							elem = ' '; //数字字符加入空格间隔符
							opnd_stack->push(opnd_stack,&elem);
							num_before_flag = 0;//加入运算符
						}
						break;
					case '=':
						optr_stack->pop(optr_stack,&elem);//脱括号
						num_before_flag = 1; //脱括号等效为加入的是数字
						break;
					case '>': //栈顶运算符优先级高
						if(num_before_flag == 0){ //前一个入栈的是符号
							if(*str == '-'){ //此时'-'号表示为负号
								opnd_stack->push(opnd_stack,str);//'-'号加入操作数栈
								num_before_flag = 1; //加入的是数字
							}else{
								printf("Expression format error!");
								break;
							}
						}else{ //前一个入栈的是数字
							optr_stack->pop(optr_stack,&opetr_char);//取运算符
							number_b = getOpndNumFromStack(opnd_stack);
							number_a = getOpndNumFromStack(opnd_stack);
							cal_result = operate(number_a,opetr_char,number_b);
							printf("%d",number_a);
							printf(" %c ",opetr_char);
							printf("%d = ",number_b);
							printf("%d\n",cal_result);
							pushResultToStack(opnd_stack, cal_result);
							num_before_flag = 1; //加入的是数字
							str--;
						}
						break;
				}
			}else{
				//第一个运算符，此时运算符栈是空的
				if(num_before_flag == 0){ //前面没有数字入栈
					if(*str == '-'){ //此时'-'号表示为负号
						opnd_stack->push(opnd_stack,str);//'-'号加入操作数栈
						num_before_flag = 1; //加入的是数字
					}else if(*str == '('){
						optr_stack->push(optr_stack,str);  
						elem = ' '; //数字字符加入空格间隔符
						opnd_stack->push(opnd_stack,&elem);
						num_before_flag = 0;//加入运算符
					}else{
						printf("Expression format error!");
						break;
					}
				}else{ //前面有数字入栈
					optr_stack->push(optr_stack,str);  
					elem = ' '; //数字字符加入空格间隔符
					opnd_stack->push(opnd_stack,&elem);
					num_before_flag = 0;//加入运算符
				}
			}
		}else{
			if(*str >= 0x30 && *str <= 0x39){
				opnd_stack->push(opnd_stack,str);
				num_before_flag = 1; //加入的是数字
			}
		}
		str++;
	}
	if(*str == '\0'){ //输入完成
		while(optr_stack->length(optr_stack)){
			optr_stack->pop(optr_stack,&opetr_char);//取运算符
			if(isOpetrChar(opetr_char)<5){
				number_b = getOpndNumFromStack(opnd_stack);
				number_a = getOpndNumFromStack(opnd_stack);
				cal_result = operate(number_a,opetr_char,number_b);
				printf("%d",number_a);
				printf(" %c ",opetr_char);
				printf("%d = ",number_b);
				printf("%d\n",cal_result);
				pushResultToStack(opnd_stack, cal_result);
			}
		}
	}
	DestroyLinearListStack(optr_stack);
	return opnd_stack;
}

int main(void)
{
	int i;
	char string[1000];
	LinearListStack *optr_result = NULL;
	printf("please enter a expression:");
	gets(string);
	optr_result = evaluateExpression(string);
	printf("%s = ",string);
	optr_result->risePrint(optr_result);
	DestroyLinearListStack(optr_result);
	return 0;
}