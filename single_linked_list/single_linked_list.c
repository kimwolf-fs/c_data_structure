#include <stdio.h>
#include <malloc.h>
#include "SingleLinkedList.h"

static void clear(SingleLinkedList *This);
static int isEmpty(SingleLinkedList *This);
static int length(SingleLinkedList *This);
static void print(SingleLinkedList *This);
static int indexElem(SingleLinkedList *This, ElemType* x);
static int getElem(SingleLinkedList *This, int index, ElemType *e);
static int modifyElem(SingleLinkedList *This, int index, ElemType* e);
static int deleteElem(SingleLinkedList *This, int index, ElemType* e);
static int appendElem(SingleLinkedList *This, ElemType *e);
static int insertElem(SingleLinkedList *This, int index, ElemType *e);
static int popElem(SingleLinkedList *This, ElemType* e);
static int reverseList1(SingleLinkedList *This);
static int reverseList2(SingleLinkedList *This);

SingleLinkedList *InitSingleLinkedList(){
	SingleLinkedList *L = (SingleLinkedList *)malloc(sizeof(SingleLinkedList));
	Node *p = (Node *)malloc(sizeof(Node));
	L->This = p;
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
	L->reverseList1 = reverseList1;
	L->reverseList2 = reverseList2;
	return L;
}

void DestroySingleLinkedList(SingleLinkedList *L){
	L->clear(L);
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(SingleLinkedList *This){
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

static int isEmpty(SingleLinkedList *This){
	Node *p = This->This;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(SingleLinkedList *This){
	int j = 0;
	Node *p = This->This->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static void print(SingleLinkedList *This){
	Node *p = This->This->next;
	while(p){
		printf("%d ", p->elem);
		p = p->next;
	} 
	printf("\n");
}

static int indexElem(SingleLinkedList *This, ElemType* e){
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

static int getElem(SingleLinkedList *This, int index, ElemType *e){
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

static int modifyElem(SingleLinkedList *This, int index, ElemType* e){
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

static int insertElem(SingleLinkedList *This, int index, ElemType *e){
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
	temp->next = p->next;
	p->next = temp;
	return 0;
}

static int deleteElem(SingleLinkedList *This, int index, ElemType* e){
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
	*e = temp->elem;
	free(temp);
	return 0;
}

static int appendElem(SingleLinkedList *This, ElemType *e){
	Node *p = This->This;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p){
		if(NULL == p->next){
			temp->elem = *e;
			p->next = temp;
			temp->next =  NULL;
		}
		p = p->next;
	} 
	return 0;
}

static int popElem(SingleLinkedList *This, ElemType* e){
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

//迭代方式
static int reverseList1(SingleLinkedList *This){
	Node *p = This->This->next;
	if (p == NULL || p->next == NULL) return -1;
	Node *temp = NULL, *newH = NULL;
	while (p != NULL){
		temp = p->next;
		p->next = newH;
		newH = p;
		p = temp;
	}
	This->This->next = newH;
	return 0;
}

//递归方式
static Node *ReverseList2(Node *head){
	if (head == NULL || head->next == NULL){
		return head;
	}else{
		Node *temp = head->next, *newH = NULL;
		head->next = NULL;
		newH = ReverseList2(temp);
		temp->next = head;
		return newH;
	}
}

static int reverseList2(SingleLinkedList *This){
	Node *p = This->This->next;
	if (p == NULL || p->next == NULL) return -1;
	This->This->next = ReverseList2(p);
	return 0;
}