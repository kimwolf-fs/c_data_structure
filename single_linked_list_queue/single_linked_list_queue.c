#include <stdio.h>
#include <malloc.h>
#include "SingleLinkedListQueue.h"

static void clear(SingleLinkedListQueue *This);
static int isEmpty(SingleLinkedListQueue *This);
static int length(SingleLinkedListQueue *This);
static QNode *getHead(SingleLinkedListQueue *This);
static int enQueue(SingleLinkedListQueue *This,QNode *n);
static int deQueue(SingleLinkedListQueue *This,QNode *n);
static int traverse(SingleLinkedListQueue *This,int (*visit)(QNode *n));

SingleLinkedListQueue *InitSingleLinkedListQueue(){
	SingleLinkedListQueue *Q = (SingleLinkedListQueue *)malloc(sizeof(SingleLinkedListQueue));
	QNode *p = (QNode *)malloc(sizeof(QNode));
	Q->This = p;
	Q->front = p;
	Q->tear = Q->front;
	p->next = NULL;
	Q->clear = clear;
	Q->isEmpty = isEmpty;
	Q->length = length;
	Q->getHead = getHead;
	Q->enQueue = enQueue;
	Q->deQueue = deQueue;
	Q->traverse = traverse;
	return Q;
}

void DestroySingleLinkedListQueue(SingleLinkedListQueue *Q){
	Q->clear(Q);
	free(Q->This);
	free(Q);
	Q = NULL;
}

static void clear(SingleLinkedListQueue *This){
	QNode *p = This->This->next;
	QNode *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->This;
	p->next = NULL;
	This->front = p;
	This->tear = This->front;
}

static int isEmpty(SingleLinkedListQueue *This){
	QNode *p = This->This;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(SingleLinkedListQueue *This){
	int j = 0;
	QNode *p = This->This->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static QNode *getHead(SingleLinkedListQueue *This){
	return This->front->next;
}

static int enQueue(SingleLinkedListQueue *This,QNode *n){
	if(!n) return -1;
	This->tear->next = n;
	n->next = NULL;
	This->tear = n;
	return 0;
}

static int deQueue(SingleLinkedListQueue *This,QNode *n){
	if(This->front == This->tear){
		n = NULL;
		return -1;
	}
	QNode *temp = This->front->next;
	*n = *(temp);
	This->front->next = temp->next; 
	if(This->tear == temp) This->tear = This->front;
	free(temp);
	return 0;
}

static int traverse(SingleLinkedListQueue *This,int (*visit)(QNode *n)){
	if(This->front == This->tear){
		return -1;
	}
	QNode *temp = This->front->next;
	while(temp){
		if(visit(temp) != 0) break;
		temp = temp->next;
	} 
	return 0;
}