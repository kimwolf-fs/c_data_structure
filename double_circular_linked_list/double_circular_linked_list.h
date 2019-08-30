/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DOUBLECIRCULARLINKEDLIST_H
#define __DOUBLECIRCULARLINKEDLIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int ElemType;      //数据元素的类型，假设是int型的

typedef struct Node{
	ElemType elem;  //存储空间
	struct Node *prior;
	struct Node *next;
}Node;

typedef struct DoubleCircularLinkedList{
	Node *This;
	void (*clear)(struct DoubleCircularLinkedList *This);
	int (*isEmpty)(struct DoubleCircularLinkedList *This);
	int (*length)(struct DoubleCircularLinkedList *This);
	void (*print)(struct DoubleCircularLinkedList *This);
	void (*circlePrint)(struct DoubleCircularLinkedList *This,int times);
	int (*indexElem)(struct DoubleCircularLinkedList *This, ElemType* x);
	int (*indexNode)(struct DoubleCircularLinkedList *This, Node* n);
	int (*getElem)(struct DoubleCircularLinkedList *This, int index, ElemType *e);
	Node *(*getNode)(struct DoubleCircularLinkedList *This, int index);
	Node *(*getPriorNode)(Node *n);
	Node *(*getNextNode)(Node *n);
	int (*modifyElem)(struct DoubleCircularLinkedList *This, int index, ElemType* e);
	int (*deleteElem)(struct DoubleCircularLinkedList *This, int index, ElemType* e);
	int (*deleteNode)(struct DoubleCircularLinkedList *This, Node* n);
	int (*appendElem)(struct DoubleCircularLinkedList *This, ElemType *e);
	int (*insertElem)(struct DoubleCircularLinkedList *This, int index, ElemType *e);
	int (*popElem)(struct DoubleCircularLinkedList *This, ElemType* e);
}DoubleCircularLinkedList;

/* Exported macro ------------------------------------------------------------*/
DoubleCircularLinkedList *InitDoubleCircularLinkedList();
void DestroyDoubleCircularLinkedList(DoubleCircularLinkedList *L);

#endif