#include <stdio.h>
#include <malloc.h>
#include "DLLQueue.h"

static void clear(DLLQueue *This);
static int isEmpty(DLLQueue *This);
static int length(DLLQueue *This);
static void riseTraverse(DLLQueue *This,int (*visit)(void **e));
static void downTraverse(DLLQueue *This,int (*visit)(void **e));
static int getHead(DLLQueue *This, void **e);
static int enQueue(DLLQueue *This, void *e);
static int deQueue(DLLQueue *This, void **e);

DLLQueue *InitDLLQueue(){
	DLLQueue *Q = (DLLQueue *)malloc(sizeof(DLLQueue));
	if(!Q) return NULL;
	DLLQNode *p = (DLLQNode *)malloc(sizeof(DLLQNode));
	if(!p){
		free(Q);
		return NULL;
	}
	Q->front = p;
	Q->tear = Q->front;
	p->prior = NULL;
	p->next = NULL;
	Q->clear = clear;
	Q->isEmpty = isEmpty;
	Q->length = length;
	Q->riseTraverse = riseTraverse;
	Q->downTraverse = downTraverse;
	Q->getHead = getHead;
	Q->enQueue = enQueue;
	Q->deQueue = deQueue;
	return Q;
}

void DestroyDLLQueue(DLLQueue *Q){
	if(Q){
		if(Q->front){
			Q->clear(Q);
			free(Q->front);
		}
		free(Q);
		Q = NULL;
	}
}

static void clear(DLLQueue *This){
	DLLQNode *p = This->front->next;
	DLLQNode *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->front;
	p->next = NULL;
	This->tear = This->front;
}

static int isEmpty(DLLQueue *This){
	DLLQNode *p = This->front;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(DLLQueue *This){
	int j = 0;
	DLLQNode *p = This->front->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static void riseTraverse(DLLQueue *This,int (*visit)(void **e)){
	DLLQNode *p = This->front->next;
	while(p){
		if(visit(&(p->elem)) != 0) break;
		p = p->next;
	} 
}

static void downTraverse(DLLQueue *This,int (*visit)(void **e)){
	DLLQNode *p = This->tear;
	while(p != This->front){
		if(visit(&(p->elem)) != 0) break;
		p = p->prior;
	} 
}


static int getHead(DLLQueue *This, void **e){
	if(isEmpty(This)) return -1;
	*e = This->front->next->elem;
	return 0;
}

static int enQueue(DLLQueue *This, void *e){
	DLLQNode *p = This->tear;
	DLLQNode *temp = (DLLQNode *)malloc(sizeof(DLLQNode));
	if(!temp) return -1;
	temp->elem = e;
	p->next = temp;
	temp->prior = p;
	This->tear = temp;
	temp->next =  NULL;
	return 0;
}

static int deQueue(DLLQueue *This, void **e){
	if(This->front == This->tear){
		*e = NULL;
		return -1;
	}
	DLLQNode *p = This->front->next;
	*e = p->elem;
	This->front->next = p->next;
	if(This->tear == p){
		This->tear = This->front;
	}else{
		p->next->prior = This->front;
	}
	free(p);
	return 0;
}

