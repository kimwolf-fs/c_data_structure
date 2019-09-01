#include <stdio.h>
#include <malloc.h>
#include "double_circular_linked_list.h"

int main(void){
	int i;
	double_circular_elem_type elem,elem1;
	struct double_circular_linked_list_node *tempn = NULL;
	struct double_circular_linked_list_node *tempm = NULL;
	struct double_circular_linked_list *list = init_double_circular_linked_list();
	printf("list is empty:%d\n",list->is_empty(list));
	for(i=0;i<10;i++){
		list->append_elem(list,&i);
	}
	list->print(list);
	printf("list is empty:%d\n",list->is_empty(list));
	printf("list length:%d\n",list->length(list));
	list->clear(list);
	for (i = 10; i < 20; i++){
		list->append_elem(list,&i);
	}	
	list->print(list);
	list->get_elem(list,3,&elem1);
	printf("the elem of index 3 is %d\n",elem1);
	elem = 31;
	list->modify_elem(list,3,&elem);
	list->get_elem(list,3,&elem1);
	printf("modify the elem of index 3 to %d\n",elem1);
	list->print(list);
	elem = 25;
	list->insert_elem(list,5,&elem);
	printf("insert elem %d to index 5\n",elem);
	list->print(list);
	elem = 14;
	printf("the index of 14 is %d\n",list->index_elem(list,&elem));
	list->pop_elem(list,&elem);
	printf("pop elem %d\n",elem);
	list->print(list);
	printf("circle print 3 times:\n");
	list->circle_print(list,3);
	tempn = list->get_node(list,5);
	printf("get node of index 5: node elem = %d\n",tempn->elem);
	printf("the index of node: %d\n",list->index_node(list, tempn));
	tempm = list->get_prior_node(tempn);
	printf("get Prior node of index 5: Prior node elem = %d\n",tempm->elem);
	tempm = list->get_next_node(tempn);
	printf("get Next node of index 5: Next node elem = %d\n",tempm->elem);
	list->delete_node(list,tempn);
	printf("delete node of index 5\n");
	list->print(list);
	destroy_double_circular_linked_list(list);
	return 0;
}