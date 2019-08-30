#include <stdio.h>
#include <malloc.h>
#include "SingleCircularLinkedListQueue.h"

static void clear(SingleCircularLinkedListQueue *This);
static int isEmpty(SingleCircularLinkedListQueue *This);
static int length(SingleCircularLinkedListQueue *This);
static QNode *getHead(SingleCircularLinkedListQueue *This);
static int enQueue(SingleCircularLinkedListQueue *This,QNode *n);
static int deQueue(SingleCircularLinkedListQueue *This,QNode *n);
static int traverse(SingleCircularLinkedListQueue *This,int (*visit)(QNode *n),int circular);

SingleCircularLinkedListQueue *InitSingleCircularLinkedListQueue(){
	SingleCircularLinkedListQueue *Q = (SingleCircularLinkedListQueue *)malloc(sizeof(SingleCircularLinkedListQueue));
	QNode *p = (QNode *)malloc(sizeof(QNode));
	Q->This = p;
	Q->front = p;
	Q->tear = Q->front;
	p->next = p;
	Q->clear = clear;
	Q->isEmpty = isEmpty;
	Q->length = length;
	Q->getHead = getHead;
	Q->enQueue = enQueue;
	Q->deQueue = deQueue;
	Q->traverse = traverse;
	return Q;
}

void DestroySingleCircularLinkedListQueue(SingleCircularLinkedListQueue *Q){
	Q->clear(Q);
	free(Q->This);
	free(Q);
	Q = NULL;
}

static void clear(SingleCircularLinkedListQueue *This){
	QNode *head = This->This;
	QNode *p = This->This->next;
	QNode *temp = NULL;
	while(p != head){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->This;
	p->next = head;
	This->front = p;
	This->tear = This->front;
}

static int isEmpty(SingleCircularLinkedListQueue *This){
	QNode *p = This->This;
	if(p->next == p){
		return 0;
	}else{
		return 1;
	}
}

static int length(SingleCircularLinkedListQueue *This){
	int j = 0;
	QNode *head = This->This;
	QNode *p = This->This->next;
	while(p != head){
		j++;
		p = p->next;
	} 
	return j;
}

static QNode *getHead(SingleCircularLinkedListQueue *This){
	return This->front->next;
}

static int enQueue(SingleCircularLinkedListQueue *This,QNode *n){
	QNode *head = This->This;
	if(!n) return -1;
	This->tear->next = n;
	n->next = head;
	This->tear = n;
	return 0;
}

static int deQueue(SingleCircularLinkedListQueue *This,QNode *n){
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

static int traverse(SingleCircularLinkedListQueue *This,int (*visit)(QNode *n),int circular){
	if(This->front == This->tear){
		return -1;
	}
	QNode *head = This->front;
	QNode *temp = This->front->next;
	if(circular){
		while(temp){
			if(temp != head){
				if(visit(temp) != 0) break;
			}
			temp = temp->next;
		} 
	}else{
		while(temp != head){
			if(visit(temp) != 0) break;
			temp = temp->next;
		}
	}
	return 0;
}