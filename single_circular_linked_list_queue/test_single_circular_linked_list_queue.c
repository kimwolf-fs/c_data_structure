#include <stdio.h>
#include <malloc.h>
#include "SingleCircularLinkedListQueue.h"

char name[][3] = {"xw","xh","xm","xg","xl","xz"};

void strCopy(char *str_a,char *str_b){
	while(*str_b != '\0'){
		*str_a++ = *str_b++;
	}
	*str_a = '\0';
}

int printQnode(QNode *node){
	printf("id:%d,name:%s\n",node->elem.id,node->elem.name);
	return 0;
}

int main(void){
	int i;
	QNode *node = NULL;
	SingleCircularLinkedListQueue *queue = InitSingleCircularLinkedListQueue();
	printf("queue is empty:%d\n",queue->isEmpty(queue));
	for(i=0;i<6;i++){
		node = (QNode *)malloc(sizeof(QNode));
		node->elem.id = i;
		strCopy(node->elem.name,name[i]);
		queue->enQueue(queue,node);
	}
	queue->traverse(queue,printQnode,0);
	printf("queue is empty:%d\n",queue->isEmpty(queue));
	printf("queue length:%d\n",queue->length(queue));
	while(queue->length(queue)){
		node = queue->getHead(queue);
		printf("present client: id=%d, name=%s\n",node->elem.id,node->elem.name);
		node = (QNode *)malloc(sizeof(QNode));
		queue->deQueue(queue,node);
		printf("client :id=%d,name=%s finish!\n",node->elem.id,node->elem.name);
		free(node);
		node = NULL;
	}
	queue->clear(queue);
	for (i = 10; i < 16; i++){
		node = (QNode *)malloc(sizeof(QNode));
		node->elem.id = i;
		strCopy(node->elem.name,name[i-10]);
		queue->enQueue(queue,node);
	}	
	queue->traverse(queue,printQnode,1);
	DestroySingleCircularLinkedListQueue(queue);
	return 0;
}