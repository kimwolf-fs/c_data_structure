#include <stdio.h>
#include <malloc.h>
#include "DLLStack.h"

static void clear(DLLStack *This);
static int isEmpty(DLLStack *This);
static int length(DLLStack *This);
static void riseTraverse(DLLStack *This,int (*visit)(void **e));
static void downTraverse(DLLStack *This,int (*visit)(void **e));
static int getTopElem(DLLStack *This, void **e);
static int pushElem(DLLStack *This, void *e);
static int popElem(DLLStack *This, void **e);

DLLStack *InitDLLStack(){
	DLLStack *S = (DLLStack *)malloc(sizeof(DLLStack));
	if(!S) return NULL;
	DLLSNode *p = (DLLSNode *)malloc(sizeof(DLLSNode));
	if(!p){
		free(S);
		return NULL;
	}
	S->front = p;
	S->tear = S->front;
	p->prior = NULL;
	p->next = NULL;
	S->clear = clear;
	S->isEmpty = isEmpty;
	S->length = length;
	S->riseTraverse = riseTraverse;
	S->downTraverse = downTraverse;
	S->getTopElem = getTopElem;
	S->pushElem = pushElem;
	S->popElem = popElem;
	return S;
}

void DestroyDLLStack(DLLStack *S){
	if(S){
		if(S->front){
			S->clear(S);
			free(S->front);
		}
		free(S);
		S = NULL;
	}
}

static void clear(DLLStack *This){
	DLLSNode *p = This->front->next;
	DLLSNode *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->front;
	p->next = NULL;
	This->tear = This->front;
}

static int isEmpty(DLLStack *This){
	DLLSNode *p = This->front;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(DLLStack *This){
	int j = 0;
	DLLSNode *p = This->front->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static void riseTraverse(DLLStack *This,int (*visit)(void **e)){
	DLLSNode *p = This->front->next;
	while(p){
		if(visit(&(p->elem)) != 0) break;
		p = p->next;
	} 
}

static void downTraverse(DLLStack *This,int (*visit)(void **e)){
	DLLSNode *p = This->tear;
	while(p != This->front){
		if(visit(&(p->elem)) != 0) break;
		p = p->prior;
	} 
}


static int getTopElem(DLLStack *This, void **e){
	if(isEmpty(This)) return -1;
	*e = This->tear->elem;
	return 0;
}

static int pushElem(DLLStack *This, void *e){
	DLLSNode *p = This->tear;
	DLLSNode *temp = (DLLSNode *)malloc(sizeof(DLLSNode));
	if(!temp) return -1;
	temp->elem = e;
	p->next = temp;
	temp->prior = p;
	This->tear = temp;
	temp->next =  NULL;
	return 0;
}

static int popElem(DLLStack *This, void **e){
	if(This->front == This->tear){
		*e = NULL;
		return -1;
	}
	DLLSNode *p = This->tear;
	DLLSNode *temp = NULL;
	temp = p->prior;
	*e = p->elem;
	free(p);
	This->tear = temp;
	temp->next = NULL;
	return 0;
}

