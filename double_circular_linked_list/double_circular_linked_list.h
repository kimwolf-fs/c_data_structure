/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DOUBLE_CIRCULAR_LINKED_LIST_H
#define __DOUBLE_CIRCULAR_LINKED_LIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int double_circular_elem_type;      //数据元素的类型，假设是int型的,这个应该在使用的文件中定义

struct double_circular_linked_list_node{		//这个应该在使用的文件中定义
	struct double_circular_linked_list_node *prior;
	struct double_circular_linked_list_node *next;
	double_circular_elem_type elem;  			//存储空间
};

struct double_circular_linked_list{
    struct double_circular_linked_list_node *head;
	void (*clear)(struct double_circular_linked_list *linked_list);
	int (*is_empty)(struct double_circular_linked_list *linked_list);
	int (*length)(struct double_circular_linked_list *linked_list);
	void (*print)(struct double_circular_linked_list *linked_list);
	void (*circle_print)(struct double_circular_linked_list *linked_list,int times);
	int (*index_elem)(struct double_circular_linked_list *linked_list, double_circular_elem_type* elem);
	int (*index_node)(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node* node);
	int (*get_elem)(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem);
	struct double_circular_linked_list_node *(*get_node)(struct double_circular_linked_list *linked_list, int index);
	struct double_circular_linked_list_node *(*get_prior_node)(struct double_circular_linked_list_node *node);
	struct double_circular_linked_list_node *(*get_next_node)(struct double_circular_linked_list_node *node);
	int (*modify_elem)(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type* elem);
	int (*insert_elem)(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem);
	int (*delete_node)(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node *node);
	int (*append_elem)(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem);
	int (*pop_elem)(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem);
};

/* Exported macro ------------------------------------------------------------*/
struct double_circular_linked_list* init_double_circular_linked_list();
void destroy_double_circular_linked_list(struct double_circular_linked_list *linked_list);

#endif