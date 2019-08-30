#include <stdio.h>
#include <malloc.h>
#include "LinearList.h"

int main(void)
{
	int i;
	ElemType elem,elem1;
	LinearList *list = InitLinearList();
	printf("list is empty:%d\n",list->isEmpty(list));
	for (i = 0; i < 10; i++){
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
	elem = 17;
	printf("the index of 17 is %d\n",list->indexElem(list,&elem));
	list->priorElem(list,&elem,&elem1);
	printf("the prior elem of 17 is %d\n",elem1);
	list->nextElem(list,&elem,&elem1);
	printf("the next elem of 17 is %d\n",elem1);
	list->getElem(list,3,&elem1);
	printf("the elem of index 3 is %d\n",elem1);
	list->modifyElem(list,3,&elem);
	list->getElem(list,3,&elem1);
	printf("modify the elem of index 3 to %d\n",elem1);
	list->print(list);
	elem = 25;
	list->insertElem(list,5,&elem);
	printf("insert elem %d to index 5\n",elem);
	list->deleteElem(list,7,&elem);
	printf("delete elem %d of index 7\n",elem);
	list->print(list);
	list->popElem(list,&elem);
	printf("pop elem %d\n",elem);
	list->print(list);
	DestroyLinearList(list);
	return 0;
}