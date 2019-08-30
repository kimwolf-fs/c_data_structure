#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

void lineEdit(){
	char elem,ch;
	LinearListStack *stack = InitLinearListStack();
	ch = getchar();
	while(ch != EOF){
		while(ch != EOF && ch != '\n'){
			switch(ch){
				case '#':
					if(stack->length(stack)){
						stack->pop(stack,&elem);
					}
					break;
				case '@':
					stack->clear(stack);
					break;
				default:
					stack->push(stack,&ch);
					break;
			}
			ch = getchar();
		}
		stack->risePrint(stack);
		stack->clear(stack);
		if(ch != EOF) ch = getchar();
	}
	DestroyLinearListStack(stack);
}

int main(void)
{
	lineEdit();
	return 0;
}