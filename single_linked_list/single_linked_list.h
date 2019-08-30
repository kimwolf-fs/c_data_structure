/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SINGLELINKEDLIST_H
#define __SINGLELINKEDLIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int single_linked_list_elem_type;      //数据元素的类型，假设是int型的

struct single_linked_list_node{
    struct single_linked_list_node *next;
    single_linked_list_elem_type elem;  //存储空间
};

typedef struct single_linked_list{
    struct single_linked_list_node *this;
	void (*clear)(struct single_linked_list *this);
	int (*isEmpty)(struct single_linked_list *this);
	int (*length)(struct single_linked_list *this);
	void (*print)(struct single_linked_list *this);
	int (*indexElem)(struct single_linked_list *this, single_linked_list_elem_type* x);
	int (*getElem)(struct single_linked_list *this, int index, single_linked_list_elem_type *e);
	int (*modifyElem)(struct single_linked_list *this, int index, single_linked_list_elem_type* e);
	int (*deleteElem)(struct single_linked_list *this, int index, single_linked_list_elem_type* e);
	int (*appendElem)(struct single_linked_list *this, single_linked_list_elem_type *e);
	int (*insertElem)(struct single_linked_list *this, int index, single_linked_list_elem_type *e);
	int (*popElem)(struct single_linked_list *this, single_linked_list_elem_type* e);
	int (*reverseList1)(struct single_linked_list *this);
	int (*reverseList2)(struct single_linked_list *this);
};

/* Exported macro ------------------------------------------------------------*/
struct  single_linked_list *init_single_linked_list();
void destroy_single_linked_list(struct  single_linked_list *list);

#endif