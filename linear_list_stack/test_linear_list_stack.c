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

int main(void)
{
	int i;
	char string[] = "abcdefgh";
	int strlength = strlen(string);
	ElemType elem;
	LinearListStack *stack = InitLinearListStack();
	printf("string length = %d\n",strlength);
	printf("stack is empty:%d\n",stack->isEmpty(stack));
	for (i = 0; i < strlength; i++){
		stack->push(stack,string+i);
	}
	printf("base to top: \n");
	stack->risePrint(stack);
	printf("top to base: \n");
	stack->downPrint(stack);
	printf("stack is empty:%d\n",stack->isEmpty(stack));
	printf("stack length:%d\n",stack->length(stack));
	for(i=0;i < strlength; i++){
		stack->getTop(stack,&elem);
		printf("get top elem:%c\n",elem);
		stack->pop(stack,&elem);
		printf("pop elem:%c\n",elem);
	}
	printf("stack is empty:%d\n",stack->isEmpty(stack));
	printf("stack length:%d\n",stack->length(stack));
	stack->clear(stack);
	DestroyLinearListStack(stack);
	return 0;
}