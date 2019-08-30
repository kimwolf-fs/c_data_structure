#include <stdio.h>
#include <malloc.h>
#include "DoubleCircularLinkedList.h"

static void clear(DoubleCircularLinkedList *This);
static int isEmpty(DoubleCircularLinkedList *This);
static int length(DoubleCircularLinkedList *This);
static void print(DoubleCircularLinkedList *This);
static void circlePrint(DoubleCircularLinkedList *This,int times);
static int indexElem(DoubleCircularLinkedList *This, ElemType* x);
static int indexNode(DoubleCircularLinkedList *This, Node* n);
static int getElem(DoubleCircularLinkedList *This, int index, ElemType *e);
static Node *getNode(DoubleCircularLinkedList *This, int index);
static Node *getPriorNode(Node *n);
static Node *getNextNode(Node *n);
static int modifyElem(DoubleCircularLinkedList *This, int index, ElemType* e);
static int deleteElem(DoubleCircularLinkedList *This, int index, ElemType* e);
static int deleteNode(DoubleCircularLinkedList *This, Node* n);
static int appendElem(DoubleCircularLinkedList *This, ElemType *e);
static int insertElem(DoubleCircularLinkedList *This, int index, ElemType *e);
static int popElem(DoubleCircularLinkedList *This, ElemType* e);

DoubleCircularLinkedList *InitDoubleCircularLinkedList(){
	DoubleCircularLinkedList *L = (DoubleCircularLinkedList *)malloc(sizeof(DoubleCircularLinkedList));
	Node *p = (Node *)malloc(sizeof(Node));
	L->This = p;
	p->prior = p;
	p->next = p;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->circlePrint = circlePrint;
	L->indexElem = indexElem;
	L->indexNode = indexNode;
	L->getElem = getElem;
	L->getNode = getNode;
	L->getPriorNode = getPriorNode;
	L->getNextNode = getNextNode;
	L->modifyElem = modifyElem;
	L->deleteElem = deleteElem;
	L->deleteNode = deleteNode;
	L->appendElem = appendElem;
	L->insertElem = insertElem;
	L->popElem = popElem;
	return L;
}

void DestroyDoubleCircularLinkedList(DoubleCircularLinkedList *L){
	L->clear(L);
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(DoubleCircularLinkedList *This){
	Node *head = This->This;
	Node *p = This->This->next;
	Node *temp = NULL;
	while(p != head){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->This;
	p->next = head;
	p->prior = head;
}

static int isEmpty(DoubleCircularLinkedList *This){
	Node *p = This->This;
	if(p->next == p){
		return 0;
	}else{
		return 1;
	}
}

static int length(DoubleCircularLinkedList *This){
	int j = 0;
	Node *head = This->This;
	Node *p = This->This->next;
	while(p != head){
		j++;
		p = p->next;
	} 
	return j;
}

static void print(DoubleCircularLinkedList *This){
	Node *head = This->This;
	Node *p = This->This->next;
	while(p != head){
		printf("%d ", p->elem);
		p = p->next;
	} 
	printf("\n");
}

static void circlePrint(DoubleCircularLinkedList *This,int times){
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

static int indexElem(DoubleCircularLinkedList *This, ElemType* e){
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

static int indexNode(DoubleCircularLinkedList *This, Node* n){
	Node *head = This->This;
	Node *p = This->This->next;
	int pos = -1;
	int j = 0;
	while(p != head){
		if(n == p){
			pos = j;
		}
		p = p->next;
		j++;
	} 
	return pos;
}

static int getElem(DoubleCircularLinkedList *This, int index, ElemType *e){
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

static Node *getNode(DoubleCircularLinkedList *This, int index){
	Node *head = This->This;
	Node *p = This->This->next;
	int j = 0;
	while(p != head && j < index){
		p = p->next;
		j++;
	} 
	if(p == head || j > index) return NULL;
	return p;
}

static Node *getPriorNode(Node *n){
	return n->prior;
}

static Node *getNextNode(Node *n){
	return n->next;
}

static int modifyElem(DoubleCircularLinkedList *This, int index, ElemType* e){
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

static int insertElem(DoubleCircularLinkedList *This, int index, ElemType *e){
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
	p->next->prior = temp;
	temp->prior = p;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

static int deleteNode(DoubleCircularLinkedList *This, Node* n){
	if(indexNode(This, n)>=0){
		n->prior->next = n->next;
		n->next->prior = n->prior;
		free(n);
	}
	return 0;
}

static int deleteElem(DoubleCircularLinkedList *This, int index, ElemType* e){
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
	temp->next->prior = p;
	*e = temp->elem;
	free(temp);
	return 0;
}

static int appendElem(DoubleCircularLinkedList *This, ElemType *e){
	Node *head = This->This;
	Node *p = This->This->next;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p->next != head){
		p = p->next;
	} 
	temp->elem = *e;
	temp->prior = p;
	temp->next =  head;
	p->next = temp;
	head->prior = temp;
	return 0;
}

static int popElem(DoubleCircularLinkedList *This, ElemType* e){
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
	head->prior = p;
	return 0;
}

