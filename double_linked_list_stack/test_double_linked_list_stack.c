#include <stdio.h>
#include <malloc.h>
#include "DLLStack.h"

int printElem(void **e){
	printf("%d",*((int *)*e));
	return 0;
}

int main(void){
	int i = 0,*elem;
	int *num = (int *)malloc(10*sizeof(int));
	if(!num) return 0;
	for(i=0;i<10;i++){
		*(num + i) = i;
	}
	DLLStack *S = InitDLLStack();
	printf("is DLLStack empty:%d\n",S->isEmpty(S));
	printf("DLLStack length:%d\n",S->length(S));
	for(i=0;i<10;i++){
		S->pushElem(S,num + i);
	}
	printf("is DLLStack empty:%d\n",S->isEmpty(S));
	printf("DLLStack length:%d\n",S->length(S));
	S->riseTraverse(S,printElem);
	printf("\n");
	S->clear(S);
	printf("is DLLStack empty:%d\n",S->isEmpty(S));
	printf("DLLStack length:%d\n",S->length(S));
	for(i=0;i<10;i++){
		*(num + i) = i*2;
		S->pushElem(S,num + i);
	}
	S->downTraverse(S,printElem);
	printf("\n");
	for(i=0;i<10;i++){
		S->getTopElem(S,(void **)(&elem));
		printf("top elem:%d\n",*elem);
		S->popElem(S,(void **)(&elem));
		printf("pop elem:%d\n",*elem);
	}
	printf("is DLLStack empty:%d\n",S->isEmpty(S));
	printf("DLLStack length:%d\n",S->length(S));
	DestroyDLLStack(S);
	free(num);
	return 0;
}





