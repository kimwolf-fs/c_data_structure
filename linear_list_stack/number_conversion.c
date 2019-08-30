#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

int strlen(char *str){
	int i = 0;
	while(*(str+i) != '\0'){
		i++;
	}
	return i;
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

LinearListStack *intToHex(int num){
	LinearListStack *stack = InitLinearListStack();
	char item;
	if(num < 0){
		num = -num;
	}else if(num == 0){
		item = 0x30;
		stack->push(stack,&item);
	}
	while(num){
		item = num % 16;
		if(item <= 9){
			item += 0x30;
		}else{
			item += 0x37;
		}
		stack->push(stack,&item);
		num /= 16;
	}
	return stack;
}

LinearListStack *intToDec(int num){
	LinearListStack *stack = InitLinearListStack();
	char item;
	if(num < 0){
		num = -num;
	}else if(num == 0){
		item = 0x30;
		stack->push(stack,&item);
	}
	while(num){
		item = num % 10;
		item += 0x30;
		stack->push(stack,&item);
		num /= 10;
	}
	return stack;
}

LinearListStack *intToOct(int num){
	LinearListStack *stack = InitLinearListStack();
	char item;
	if(num < 0){
		num = -num;
	}else if(num == 0){
		item = 0x30;
		stack->push(stack,&item);
	}
	while(num){
		item = num % 8;
		item += 0x30;
		stack->push(stack,&item);
		num /= 8;
	}
	return stack;
}

LinearListStack *intToBin(int num){
	LinearListStack *stack = InitLinearListStack();
	char item;
	if(num < 0){
		num = -num;
	}else if(num == 0){
		item = 0x30;
		stack->push(stack,&item);
	}
	while(num){
		item = num % 2;
		item += 0x30;
		stack->push(stack,&item);
		num /= 2;
	}
	return stack;
}

void displayConvert(int num){
	int negative = 0;
	LinearListStack *stack = NULL;;
	negative = num < 0 ? 1 : 0;
	stack = intToDec(num);
	negative ? printf("DEC: -") : printf("DEC: ");
	stack->downPrint(stack);
	DestroyLinearListStack(stack);
	stack = intToHex(num);
	negative ? printf("HEX: -0X") : printf("HEX: 0X");
	stack->downPrint(stack);
	DestroyLinearListStack(stack);
	if(negative){
		stack = intToHex(0XFFFF + num + 1);
		printf("HEX negative number saved form: 0X");
		stack->downPrint(stack);
	}
	DestroyLinearListStack(stack);
	stack = intToOct(num);
	negative ? printf("OCT: -o") : printf("OCT: o");
	stack->downPrint(stack);
	DestroyLinearListStack(stack);
		if(negative){
		stack = intToOct(0XFFFF + num + 1);
		printf("OCT negative number saved form: o");
		stack->downPrint(stack);
	}
	DestroyLinearListStack(stack);
	stack = intToBin(num);
	negative ? printf("BIN: -b") : printf("BIN: b");
	stack->downPrint(stack);
	DestroyLinearListStack(stack);
	if(negative){
		stack = intToBin(0XFFFF + num + 1);
		printf("BIN negative number saved form: b");
		stack->downPrint(stack);
	}
	DestroyLinearListStack(stack);
}

int stringToInt(char *str){
	int basenum = 0,i = 0,num = 0;
	int stack_length = 0;
	int start_save = 0;
	int negative = 0;
	char item;
	LinearListStack *stack = InitLinearListStack();
	while(*str != '\0'){
		if(start_save != 1){
			if(*str == '-'){
				negative = 1;
			}else if(*str == 'o' || *str == 'O'){
				start_save = 1;
				basenum = 8;
			}else if(*str == 'b' || *str == 'B'){
				start_save = 1;
				basenum = 2;
			}else if(*str == 'd' || *str == 'D'){
				start_save = 1;
				basenum = 10;
			}else if(*str == 'x' || *str == 'X'){
				if(start_save == 2){
					start_save = 1;
					basenum = 16;
				}
			}else if(*str == '0'){
				start_save = 2;
			}
		}else if(start_save == 1){
			stack->push(stack,str);
		}
		str++;
	}
	stack_length = stack->length(stack);
	for(i=0;i<stack_length;i++){
		stack->pop(stack,&item);
		if(item >= 0x30 && item <= 0x39){
			item -= 0x30;
		}else if(item >= 0x41 && item <= 0x46){
			if(basenum == 16){
				item -= 0x37;
			}else{
				printf("Num string formal error!\n");
				DestroyLinearListStack(stack);
				return 0;
			}
		}else if(item >= 0x61 && item <= 0x66){
			if(basenum == 16){
				item -= 0x57;
			}else{
				printf("Num string formal error!\n");
				DestroyLinearListStack(stack);
				return 0;
			}
		}else{
				printf("Num string formal error!\n");
				DestroyLinearListStack(stack);
				return 0;
		}
		num += my_pow(basenum,i)*item;
	}
	DestroyLinearListStack(stack);
	if(negative) num = -num;
	return num;
}

int main(void)
{
	int num;
	char str[100];
	printf("please enter a num!\n");
	printf("num format just like these:\n");
	printf("HEX: -0X1F -0x1F 0x1F 0X1F\n");
	printf("DEC: -D11 -d11 D11 d11\n");
	printf("OCT: -O11 -o11 O11 o11\n");
	printf("BIN: -B10 -b10 B10 b10\n");
	printf("Enter:\n");
	gets(str);
	printf("\n");
	num = stringToInt(str);
	displayConvert(num);
	return 0;
}