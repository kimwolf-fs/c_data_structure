#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

int bracketMatching(char *str){
	char elem;
	int result = 0;
	int bracket_contained = 0;
	LinearListStack *stack = InitLinearListStack();
	while(*str != '\0'){
		if(*str == '{' || *str == '[' || *str == '('){
			bracket_contained = 1;
			stack->push(stack,str);
		}else if(*str == '}'){
			bracket_contained = 1;
			if(stack->length(stack)){
				stack->getTop(stack,&elem);
				if(elem == '{'){
					stack->pop(stack,&elem);
				}else if(elem == '('){
					printf("Bracket matching failed : \')\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}else if(elem == '['){
					printf("Bracket matching failed : \']\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}
			}else{
				printf("Bracket matching failed : \'{\' expected! \n");
				DestroyLinearListStack(stack);
				return 0;
			}
		}else if(*str == ']'){
			bracket_contained = 1;
			if(stack->length(stack)){
				stack->getTop(stack,&elem);
				if(elem == '['){
					stack->pop(stack,&elem);
				}else if(elem == '{'){
					printf("Bracket matching failed : \'}\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}else if(elem == '('){
					printf("Bracket matching failed : \')\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}
			}else{
				printf("Bracket matching failed : \'[\' expected! \n");
				DestroyLinearListStack(stack);
				return 0;
			}
		}else if(*str == ')'){
			bracket_contained = 1;
			if(stack->length(stack)){
				stack->getTop(stack,&elem);
				if(elem == '('){
					stack->pop(stack,&elem);
				}else if(elem == '['){
					printf("Bracket matching failed : \']\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}else if(elem == '{'){
					printf("Bracket matching failed : \'}\' expected! \n");
					DestroyLinearListStack(stack);
					return 0;
				}
			}else{
				printf("Bracket matching failed : \'(\' expected! \n");
				DestroyLinearListStack(stack);
				return 0;
			}
		}
		str++;
	}
	if(bracket_contained){
		if(stack->length(stack) == 0){
			printf("Bracket matching successed\n");
			result = 1;	
		}else{
			stack->getTop(stack,&elem);
			switch(elem){
				case '{':
					printf("Bracket matching failed : \'}\' expected! \n");
					break;
				case '[':
					printf("Bracket matching failed : \']\' expected! \n");
					break;
				case '(':
					printf("Bracket matching failed : \')\' expected! \n");
					break;
			}
			result = 0;
		}
	}else{
		printf("String doesn't contain bracket!\n");
		result = 0;
	}
	DestroyLinearListStack(stack);
	return result;
}

int main(void)
{
	int num;
	char str[100];
	printf("please enter a string!\n");
	gets(str);
	printf("\n");
	bracketMatching(str);
	return 0;
}