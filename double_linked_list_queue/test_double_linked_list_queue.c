#include <stdio.h>
#include <malloc.h>
#include "DLLQueue.h"

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
	DLLQueue *Q = InitDLLQueue();
	printf("is DLLQueue empty:%d\n",Q->isEmpty(Q));
	printf("DLLQueue length:%d\n",Q->length(Q));
	for(i=0;i<10;i++){
		Q->enQueue(Q,num + i);
	}
	printf("is DLLQueue empty:%d\n",Q->isEmpty(Q));
	printf("DLLQueue length:%d\n",Q->length(Q));
	Q->riseTraverse(Q,printElem);
	printf("\n");
	Q->clear(Q);
	printf("is DLLQueue empty:%d\n",Q->isEmpty(Q));
	printf("DLLQueue length:%d\n",Q->length(Q));
	for(i=0;i<10;i++){
		*(num + i) = i*2;
		Q->enQueue(Q,num + i);
	}
	Q->downTraverse(Q,printElem);
	printf("\n");
	for(i=0;i<10;i++){
		Q->getHead(Q,(void **)&elem);
		printf("Head elem:%d\n",*elem);
		Q->deQueue(Q,(void **)&elem);
		printf("deQueue elem:%d\n",*elem);
	}
	printf("is DLLQueue empty:%d\n",Q->isEmpty(Q));
	printf("DLLQueue length:%d\n",Q->length(Q));
	DestroyDLLQueue(Q);
	free(num);
	return 0;
}





