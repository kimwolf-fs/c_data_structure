/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DOUBLELINKEDLIST_H
#define __DOUBLELINKEDLIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int ElemType;      //数据元素的类型，假设是int型的

typedef struct Node{
	ElemType elem;  //存储空间
	struct Node *prior;
	struct Node *next;
}Node;

typedef struct DoubleLinkedList{
	Node *This;
	void (*clear)(struct DoubleLinkedList *This);
	int (*isEmpty)(struct DoubleLinkedList *This);
	int (*length)(struct DoubleLinkedList *This);
	void (*print)(struct DoubleLinkedList *This);
	int (*indexElem)(struct DoubleLinkedList *This, ElemType* x);
	int (*getElem)(struct DoubleLinkedList *This, int index, ElemType *e);
	int (*modifyElem)(struct DoubleLinkedList *This, int index, ElemType* e);
	int (*deleteElem)(struct DoubleLinkedList *This, int index, ElemType* e);
	int (*appendElem)(struct DoubleLinkedList *This, ElemType *e);
	int (*insertElem)(struct DoubleLinkedList *This, int index, ElemType *e);
	int (*popElem)(struct DoubleLinkedList *This, ElemType* e);
}DoubleLinkedList;

/* Exported macro ------------------------------------------------------------*/
DoubleLinkedList *InitDoubleLinkedList();
void DestroyDoubleLinkedList(DoubleLinkedList *L);

#endif