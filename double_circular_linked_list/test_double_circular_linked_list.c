#include <stdio.h>
#include <malloc.h>
#include "DoubleCircularLinkedList.h"

int main(void){
	int i;
	ElemType elem,elem1;
	Node *tempn = NULL;;
	Node *tempm = NULL;;
	DoubleCircularLinkedList *list = InitDoubleCircularLinkedList();
	printf("list is empty:%d\n",list->isEmpty(list));
	for(i=0;i<10;i++){
		list->appendElem(list,&i);
	}
	list->print(list);
	printf("list is empty:%d\n",list->isEmpty(list));
	printf("list length:%d\n",list->length(list));
	list->clear(list);
	for (i = 10; i < 20; i++){
		list->appendElem(list,&i);
	}	
	list->print(list);
	list->getElem(list,3,&elem1);
	printf("the elem of index 3 is %d\n",elem1);
	elem = 31;
	list->modifyElem(list,3,&elem);
	list->getElem(list,3,&elem1);
	printf("modify the elem of index 3 to %d\n",elem1);
	list->print(list);
	elem = 25;
	list->insertElem(list,5,&elem);
	printf("insert elem %d to index 5\n",elem);
	list->print(list);
	list->deleteElem(list,7,&elem);
	printf("delete elem %d of index 7\n",elem);
	list->print(list);
	elem = 14;
	printf("the index of 14 is %d\n",list->indexElem(list,&elem));
	list->popElem(list,&elem);
	printf("pop elem %d\n",elem);
	list->print(list);
	printf("circle print 3 times:\n");
	list->circlePrint(list,3);
	tempn = list->getNode(list,5);
	printf("get node of index 5: node elem = %d\n",tempn->elem);
	printf("the index of node: %d\n",list->indexNode(list, tempn));
	tempm = list->getPriorNode(tempn);
	printf("get Prior node of index 5: Prior node elem = %d\n",tempm->elem);
	tempm = list->getNextNode(tempn);
	printf("get Next node of index 5: Next node elem = %d\n",tempm->elem);
	list->deleteNode(list,tempn);
	printf("delete node of index 5\n");
	list->print(list);
	DestroyDoubleCircularLinkedList(list);
	return 0;
}