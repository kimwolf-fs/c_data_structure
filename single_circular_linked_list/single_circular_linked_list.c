#include <stdio.h>
#include <malloc.h>
#include "SingleCircularLinkedList.h"

static void clear(SingleCircularLinkedList *This);
static int isEmpty(SingleCircularLinkedList *This);
static int length(SingleCircularLinkedList *This);
static void print(SingleCircularLinkedList *This);
static void circlePrint(SingleCircularLinkedList *This,int times);
static int indexElem(SingleCircularLinkedList *This, ElemType* x);
static int getElem(SingleCircularLinkedList *This, int index, ElemType *e);
static int modifyElem(SingleCircularLinkedList *This, int index, ElemType* e);
static int deleteElem(SingleCircularLinkedList *This, int index, ElemType* e);
static int appendElem(SingleCircularLinkedList *This, ElemType *e);
static int insertElem(SingleCircularLinkedList *This, int index, ElemType *e);
static int popElem(SingleCircularLinkedList *This, ElemType* e);

SingleCircularLinkedList *InitSingleCircularLinkedList(){
	SingleCircularLinkedList *L = (SingleCircularLinkedList *)malloc(sizeof(SingleCircularLinkedList));
	Node *p = (Node *)malloc(sizeof(Node));
	L->This = p;
	p->next = p;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->circlePrint = circlePrint;
	L->indexElem = indexElem;
	L->getElem = getElem;
	L->modifyElem = modifyElem;
	L->deleteElem = deleteElem;
	L->appendElem = appendElem;
	L->insertElem = insertElem;
	L->popElem = popElem;
	return L;
}

void DestroySingleCircularLinkedList(SingleCircularLinkedList *L){
	L->clear(L);
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(SingleCircularLinkedList *This){
	Node *head = This->This;
	Node *p = This->This->next;
	Node *temp = NULL;
	while(p != head){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p->next = head;
}

static int isEmpty(SingleCircularLinkedList *This){
	Node *p = This->This;
	if(p->next == p){
		return 0;
	}else{
		return 1;
	}
}

static int length(SingleCircularLinkedList *This){
	int j = 0;
	Node *head = This->This;
	Node *p = This->This->next;
	while(p != head){
		j++;
		p = p->next;
	} 
	return j;
}

static void print(SingleCircularLinkedList *This){
	Node *head = This->This;
	Node *p = This->This->next;
	while(p != head){
		printf("%d ", p->elem);
		p = p->next;
	} 
	printf("\n");
}

static void circlePrint(SingleCircularLinkedList *This,int times){
	Node *head = This->This;
	int i = 0;
	Node *p = This->This->next;
	for(i = 0;i<times;){
		if(p == head){
			i++;
		}else{
			printf("%d ", p->elem);
		}
		p = p->next;
	}
	printf("\n");
}

static int indexElem(SingleCircularLinkedList *This, ElemType* e){
	Node *head = This->This;
	Node *p = This->This->next;
	int pos = -1;
	int j = 0;
	while(p != head){
		if(*e == p->elem){
			pos = j;
		}
		p = p->next;
		j++;
	} 
	return pos;
}

static int getElem(SingleCircularLinkedList *This, int index, ElemType *e){
	Node *head = This->This;
	Node *p = This->This->next;
	int j = 0;
	while(p != head && j < index){
		p = p->next;
		j++;
	} 
	if(p == head || j > index) return -1;
	*e = p->elem;
	return 0;
}

static int modifyElem(SingleCircularLinkedList *This, int index, ElemType* e){
	Node *head = This->This;
	Node *p = This->This->next;
	int j = 0;
	while(p != head && j < index){
		p = p->next;
		j++;
	} 
	if(p == head || j > index) return -1;
	p->elem = *e;
	return 0;
}

static int insertElem(SingleCircularLinkedList *This, int index, ElemType *e){
	Node *head = This->This;
	Node *p = This->This;
	int j = 0;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p->next != head && j < index){
		p = p->next;
		j++;
	} 
	if(p->next == head || j > index) return -1;
	temp->elem = *e;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

static int deleteElem(SingleCircularLinkedList *This, int index, ElemType* e){
	Node *head = This->This;
	Node *p = This->This;
	Node *temp = NULL;
	int j = 0;
	while(p->next != head && j < index){
		p = p->next;
		j++;
	} 
	if(p->next == head || j > index) return -1;
	temp = p->next;
	p->next = temp->next;
	*e = temp->elem;
	free(temp);
	return 0;
}

static int appendElem(SingleCircularLinkedList *This, ElemType *e){
	Node *head = This->This;
	Node *p = This->This->next;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p->next != head){
		p = p->next;
	} 
	temp->elem = *e;
	p->next = temp;
	temp->next = head;
	return 0;
}

static int popElem(SingleCircularLinkedList *This, ElemType* e){
	Node *head = This->This;
	Node *p = This->This;
	Node *temp = NULL;
	while(p->next->next != head){
		p = p->next;
	} 
	temp = p->next;
	if(temp == head) return -1;
	*e = temp->elem;
	free(temp);
	p->next = head;
	return 0;
}

