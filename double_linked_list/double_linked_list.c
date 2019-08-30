#include <stdio.h>
#include <malloc.h>
#include "DoubleLinkedList.h"

static void clear(DoubleLinkedList *This);
static int isEmpty(DoubleLinkedList *This);
static int length(DoubleLinkedList *This);
static void print(DoubleLinkedList *This);
static int indexElem(DoubleLinkedList *This, ElemType* x);
static int getElem(DoubleLinkedList *This, int index, ElemType *e);
static int modifyElem(DoubleLinkedList *This, int index, ElemType* e);
static int deleteElem(DoubleLinkedList *This, int index, ElemType* e);
static int appendElem(DoubleLinkedList *This, ElemType *e);
static int insertElem(DoubleLinkedList *This, int index, ElemType *e);
static int popElem(DoubleLinkedList *This, ElemType* e);

DoubleLinkedList *InitDoubleLinkedList(){
	DoubleLinkedList *L = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
	Node *p = (Node *)malloc(sizeof(Node));
	L->This = p;
	p->prior = NULL;
	p->next = NULL;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->indexElem = indexElem;
	L->getElem = getElem;
	L->modifyElem = modifyElem;
	L->deleteElem = deleteElem;
	L->appendElem = appendElem;
	L->insertElem = insertElem;
	L->popElem = popElem;
	return L;
}

void DestroyDoubleLinkedList(DoubleLinkedList *L){
	L->clear(L);
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(DoubleLinkedList *This){
	Node *p = This->This->next;
	Node *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->This;
	p->next = NULL;
}

static int isEmpty(DoubleLinkedList *This){
	Node *p = This->This;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(DoubleLinkedList *This){
	int j = 0;
	Node *p = This->This->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static void print(DoubleLinkedList *This){
	Node *p = This->This->next;
	while(p){
		printf("%d ", p->elem);
		p = p->next;
	} 
	printf("\n");
}

static int indexElem(DoubleLinkedList *This, ElemType* e){
	Node *p = This->This->next;
	int pos = -1;
	int j = 0;
	while(p){
		if(*e == p->elem){
			pos = j;
		}
		p = p->next;
		j++;
	} 
	return pos;
}

static int getElem(DoubleLinkedList *This, int index, ElemType *e){
	Node *p = This->This->next;
	int j = 0;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	*e = p->elem;
	return 0;
}

static int modifyElem(DoubleLinkedList *This, int index, ElemType* e){
	Node *p = This->This->next;
	int j = 0;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	p->elem = *e;
	return 0;
}

static int insertElem(DoubleLinkedList *This, int index, ElemType *e){
	Node *p = This->This;
	int j = 0;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	temp->elem = *e;
	p->next->prior = temp;
	temp->prior = p;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

static int deleteElem(DoubleLinkedList *This, int index, ElemType* e){
	Node *p = This->This;
	Node *temp = NULL;
	int j = 0;
	while(p->next && j < index){
		p = p->next;
		j++;
	} 
	if(!p->next || j > index) return -1;
	temp = p->next;
	p->next = temp->next;
	temp->next->prior = p;
	*e = temp->elem;
	free(temp);
	return 0;
}

static int appendElem(DoubleLinkedList *This, ElemType *e){
	Node *p = This->This;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p){
		if(NULL == p->next){
			temp->elem = *e;
			p->next = temp;
			temp->prior = p;
			temp->next =  NULL;
		}
		p = p->next;
	} 
	return 0;
}

static int popElem(DoubleLinkedList *This, ElemType* e){
	Node *p = This->This;
	Node *temp = NULL;
	while(p->next->next){
		p = p->next;
	} 
	temp = p->next;
	if(!temp) return -1;
	*e = temp->elem;
	free(temp);
	p->next = NULL;
	return 0;
}

