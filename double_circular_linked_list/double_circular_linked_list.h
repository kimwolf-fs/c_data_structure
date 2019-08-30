/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DOUBLE_CIRCULAR_LINKED_LIST_H
#define __DOUBLE_CIRCULAR_LINKED_LIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int ElemType;      //数据元素的类型，假设是int型的

struct double_circular_linked_list_node{
	ElemType elem;  //存储空间
	struct Node *prior;
	struct Node *next;
};

struct double_circular_linked_list{
	double_circular_linked_list_node *This;
	void (*clear)(struct double_circular_linked_list *This);
	int (*isEmpty)(struct double_circular_linked_list *This);
	int (*length)(struct double_circular_linked_list *This);
	void (*print)(struct double_circular_linked_list *This);
	void (*circlePrint)(struct double_circular_linked_list *This,int times);
	int (*indexElem)(struct double_circular_linked_list *This, ElemType* x);
	int (*indexNode)(struct double_circular_linked_list *This, double_circular_linked_list_node* n);
	int (*getElem)(struct double_circular_linked_list *This, int index, ElemType *e);
	double_circular_linked_list_node *(*getNode)(struct double_circular_linked_list *This, int index);
	double_circular_linked_list_node *(*getPriorNode)(double_circular_linked_list_node *n);
	double_circular_linked_list_node *(*getNextNode)(double_circular_linked_list_node *n);
	int (*modifyElem)(struct double_circular_linked_list *This, int index, ElemType* e);
	int (*deleteElem)(struct double_circular_linked_list *This, int index, ElemType* e);
	int (*deleteNode)(struct double_circular_linked_list *This, Node* n);
	int (*appendElem)(struct double_circular_linked_list *This, ElemType *e);
	int (*insertElem)(struct double_circular_linked_list *This, int index, ElemType *e);
	int (*popElem)(struct double_circular_linked_list *This, ElemType* e);
};

/* Exported macro ------------------------------------------------------------*/
double_circular_linked_list *InitDoubleCircularLinkedList();
void destroy_double_circular_linked_list(DoubleCircularLinkedList *L);

#endif