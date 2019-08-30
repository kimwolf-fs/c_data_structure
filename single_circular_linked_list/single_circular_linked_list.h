/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SINGLECIRCULARLINKEDLIST_H
#define __SINGLECIRCULARLINKEDLIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int ElemType;      //数据元素的类型，假设是int型的

typedef struct Node{
	ElemType elem;  //存储空间
	struct Node *next;
}Node;

typedef struct SingleCircularLinkedList{
	Node *This;
	void (*clear)(struct SingleCircularLinkedList *This);
	int (*isEmpty)(struct SingleCircularLinkedList *This);
	int (*length)(struct SingleCircularLinkedList *This);
	void (*print)(struct SingleCircularLinkedList *This);
	void (*circlePrint)(struct SingleCircularLinkedList *This,int times);
	int (*indexElem)(struct SingleCircularLinkedList *This, ElemType* x);
	int (*getElem)(struct SingleCircularLinkedList *This, int index, ElemType *e);
	int (*modifyElem)(struct SingleCircularLinkedList *This, int index, ElemType* e);
	int (*deleteElem)(struct SingleCircularLinkedList *This, int index, ElemType* e);
	int (*appendElem)(struct SingleCircularLinkedList *This, ElemType *e);
	int (*insertElem)(struct SingleCircularLinkedList *This, int index, ElemType *e);
	int (*popElem)(struct SingleCircularLinkedList *This, ElemType* e);
}SingleCircularLinkedList;

/* Exported macro ------------------------------------------------------------*/
SingleCircularLinkedList *InitSingleCircularLinkedList();
void DestroySingleCircularLinkedList(SingleCircularLinkedList *L);

#endif