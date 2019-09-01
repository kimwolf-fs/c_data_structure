#include <stdio.h>
#include <malloc.h>
#include "double_circular_linked_list.h"

static void clear(struct double_circular_linked_list *linked_list);
static int is_empty(struct double_circular_linked_list *linked_list);
static int length(struct double_circular_linked_list *linked_list);
static void print(struct double_circular_linked_list *linked_list);
static void circle_print(struct double_circular_linked_list *linked_list,int times);
static int index_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type* elem);
static int index_node(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node* node);
static int get_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem);
static struct double_circular_linked_list_node *get_node(struct double_circular_linked_list *linked_list, int index);
static struct double_circular_linked_list_node *get_prior_node(struct double_circular_linked_list_node *node);
static struct double_circular_linked_list_node *get_next_node(struct double_circular_linked_list_node *node);
static int modify_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type* elem);
static int insert_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem);
static int delete_node(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node *node);
static int append_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem);
static int pop_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem);

//初始化链表
struct double_circular_linked_list *init_double_circular_linked_list(){
	//创建双循环链表类
    struct double_circular_linked_list *linked_list =
    		(struct double_circular_linked_list *)malloc(sizeof(struct double_circular_linked_list));
	//创建头结点
    struct double_circular_linked_list_node *node =
    		(struct double_circular_linked_list_node *)malloc(sizeof(struct double_circular_linked_list_node));
    linked_list->head = node;  //链表实例的this指向头结点
    node->prior = node;     //只有一个节点，上一个也指向这个节点
    node->next = node;      //只有一个节点，下一个也指向这个节点
    linked_list->clear = clear;
	linked_list->is_empty = is_empty;
	linked_list->length = length;
	linked_list->print = print;
	linked_list->circle_print = circle_print;
	linked_list->index_elem = index_elem;
	linked_list->index_node = index_node;
	linked_list->get_elem = get_elem;
	linked_list->get_node = get_node;
	linked_list->get_prior_node = get_prior_node;
	linked_list->get_next_node = get_next_node;
	linked_list->modify_elem = modify_elem;
	linked_list->delete_node = delete_node;
	linked_list->append_elem = append_elem;
	linked_list->insert_elem = insert_elem;
	linked_list->pop_elem = pop_elem;
	return linked_list;
}

//销毁
void destroy_double_circular_linked_list(struct double_circular_linked_list *linked_list){
    linked_list->clear(linked_list);
	free(linked_list->head);
	free(linked_list);
    linked_list = NULL;
}

//清除链表
//会清除链表中的所有元素
static void clear(struct double_circular_linked_list *linked_list){
    struct double_circular_linked_list_node *head = linked_list->head;
    struct double_circular_linked_list_node *next = linked_list->head->next;
    struct double_circular_linked_list_node *temp = NULL;
    while(next != head){
        temp = next;
        next = next->next;
        free(temp);
    }
	head->prior = head;
	head->next = head;
}

//判断链表是不是为空
//返回0为空，1非空
static int is_empty(struct double_circular_linked_list *linked_list){
	struct double_circular_linked_list_node *head = linked_list->head;
	if(head->next == head){
		return 0;
	}else{
		return 1;
	}
}

//获取链表长度
static int length(struct double_circular_linked_list *linked_list){
	int j = 0;
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	while(next != head){
		j++;
		next = next->next;
	} 
	return j;
}

//打印链表中的所有元素
static void print(struct double_circular_linked_list *linked_list){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	while(next != head){
		printf("%d ", next->elem);
		next = next->next;
	}
	printf("\n");
}

//循环打印times次
static void circle_print(struct double_circular_linked_list *linked_list,int times){
	struct double_circular_linked_list_node *head = linked_list->head;
	int i = 0;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	for(i = 0; i<times; ){
		if(next == head){
			i++;
		}else{
			printf("%d ", next->elem);
		}
		next = next->next;
	}
	printf("\n");
}

//返回元素再链表中的位置
//返回-1 没有该元素
static int index_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type* elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int pos = -1;
	int j = 0;
	while(next != head){
		if(*elem == next->elem){
			pos = j;
		}
		next = next->next;
		j++;
	} 
	return pos;
}

//返回node在链表中的位置
static int index_node(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node* node){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int pos = -1;
	int j = 0;
	while(next != head){
		if(node == next){
			pos = j;
		}
		next = next->next;
		j++;
	} 
	return pos;
}

//获取 index 位置的元素
static int get_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int j = 0;
	while(next != head && j < index){
		next = next->next;
		j++;
	} 
	if(next == head || j > index){
		return -1;
	}
	*elem = next->elem;
	return 0;
}

//返回 index 位置的 node
static struct double_circular_linked_list_node *get_node(struct double_circular_linked_list *linked_list, int index){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int j = 0;
	while(next != head && j < index){
		next = next->next;
		j++;
	} 
	if(next == head || j > index) return NULL;
	return next;
}

//返回上一个节点
static struct double_circular_linked_list_node *get_prior_node(struct double_circular_linked_list_node *node){
	return node->prior;
}

//返回 node 的下一个节点
static struct double_circular_linked_list_node *get_next_node(struct double_circular_linked_list_node *node){
	return node->next;
}

//修改 index 位置的元素值
static int modify_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type* elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int j = 0;
	while(next != head && j < index){
		next = next->next;
		j++;
	} 
	if(next == head || j > index) return -1;
	next->elem = *elem;
	return 0;
}

//在 index 位置插入元素
static int insert_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type *elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	int j = 0;
	//创造一个中间节点
	struct double_circular_linked_list_node *temp =
			(struct double_circular_linked_list_node *)malloc(sizeof(struct double_circular_linked_list_node));
	if(!temp){
		return -1;
	}
	//找到 index 的位置
	while(next->next != head && j < index){
		next = next->next;
		j++;
	} 
	if(next->next == head || j > index){
		return -1;
	}
	temp->elem = *elem;
	next->next->prior = temp;
	temp->prior = next;
	temp->next = next->next;
	next->next = temp;
	return 0;
}

//删除 node 节点
static int delete_node(struct double_circular_linked_list *linked_list, struct double_circular_linked_list_node *node){
	if(index_node(linked_list, node)>=0){
		node->prior->next = node->next;
		node->next->prior = node->prior;
		free(node);
	}
	return 0;
}

static int delete_elem(struct double_circular_linked_list *linked_list, int index, double_circular_elem_type* elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	struct double_circular_linked_list_node *temp = NULL;
	int j = 0;
	while(next->next != head && j < index){
		next = next->next;
		j++;
	} 
	if(next->next == head || j > index) return -1;
	temp = next->next;
	next->next = temp->next;
	temp->next->prior = next;
	*elem = temp->elem;
	free(temp);
	return 0;
}

//在尾部添加元素
static int append_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	struct double_circular_linked_list_node *temp =
			(struct double_circular_linked_list_node *)malloc(sizeof(struct double_circular_linked_list_node));
	if(!temp) return -1;
	while(next->next != head){
		next = next->next;
	}
	temp->elem = *elem;
	temp->prior = next;
	temp->next =  head;
	next->next = temp;
	head->prior = temp;
	return 0;
}

static int pop_elem(struct double_circular_linked_list *linked_list, double_circular_elem_type *elem){
	struct double_circular_linked_list_node *head = linked_list->head;
	struct double_circular_linked_list_node *next = linked_list->head->next;
	struct double_circular_linked_list_node *temp = NULL;
	while(next->next->next != head){
		next = next->next;
	}
	temp = next->next;
	if(temp == head){
		return -1;
	}
	*elem = temp->elem;
	free(temp);
	next->next = head;
	head->prior = next;
	return 0;
}

