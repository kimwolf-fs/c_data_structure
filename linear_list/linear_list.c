#include <stdio.h>
#include <malloc.h>
#include "LinearList.h"
//线性表

static void clear(LinearList *This);
static int isEmpty(LinearList *This);
static int length(LinearList *This);
static void print(LinearList *This);
static int indexElem(LinearList *This, ElemType* x);
static int priorElem(LinearList *This, ElemType* cur_elem, ElemType* pre_elem);
static int getElem(LinearList *This, int index, ElemType* e);
static int modifyElem(LinearList *This, int index, ElemType* e);
static int nextElem(LinearList *This, ElemType* cur_elem, ElemType* next_elem);
static int insertElem(LinearList *This, int index, ElemType* e);
static int deleteElem(LinearList *This, int index, ElemType* e);
static int appendElem(LinearList *This,ElemType* e);
static int popElem(LinearList *This, ElemType* e);

LinearList *InitLinearList(){
	LinearList *L = (LinearList *)malloc(sizeof(LinearList));
	LinearList_P *p = (LinearList_P *)malloc(sizeof(LinearList_P));
	p->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	p->length = 0; //当前长度
	p->size = LIST_INIT_SIZE; //当前分配量
	L->This = p;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->indexElem = indexElem;
	L->priorElem = priorElem;
	L->getElem = getElem;
	L->modifyElem = modifyElem;
	L->nextElem = nextElem;
	L->insertElem = insertElem;
	L->deleteElem = deleteElem;
	L->appendElem = appendElem;
	L->popElem = popElem;
	return L;
}

void DestroyLinearList(LinearList *L){
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(LinearList *This){
	LinearList_P *p = This->This;
	p->length = 0; //当前长度
}

static int isEmpty(LinearList *This){
	LinearList_P *p = This->This;
	return (p->length == 0);
}

static int length(LinearList *This){
	LinearList_P *p = This->This;
	return p->length;
}

static void print(LinearList *This){
	LinearList_P *p = This->This;
	int i;
	for (i=0; i < p->length; i++){
		printf("%d ", p->elem[i]);
	}
	printf("\n");
}

static int indexElem(LinearList *This, ElemType* x){
	LinearList_P *p = This->This;
	int pos = -1;
	for (int i = 0; i < p->length; i++){
		if (p->elem[i] == *x){
			pos = i;
		}
	}
	return pos;
}

static int priorElem(LinearList *This, ElemType* cur_elem, ElemType* pre_elem){
	LinearList_P *p = This->This;
	int pos = -1;
	pos = indexElem(This, cur_elem);
	if(pos <= 0) return -1;
	*pre_elem = p->elem[pos-1];
	return 0;
}

static int getElem(LinearList *This, int index, ElemType* e){
	LinearList_P *p = This->This;
	if (index<0 || index >= p->length) return -1;
	*e = p->elem[index];
	return 0;
}

static int modifyElem(LinearList *This, int index, ElemType* e){
	LinearList_P *p = This->This;
	if (index<0 || index >= p->length) return -1;
	p->elem[index] = *e;
	return 0;
}

static int nextElem(LinearList *This, ElemType* cur_elem, ElemType* next_elem){
	LinearList_P *p = This->This;
	int pos = -1;
	pos = indexElem(This, cur_elem);
	if(pos == -1 || pos == (p->length - 1)) return -1;
	*next_elem = p->elem[pos+1];
	return 0;
}

static int insertElem(LinearList *This, int index, ElemType* e){
	LinearList_P *p = This->This;
	if (index<0 || index >= p->length) return -1;
	if (p->length >= p->size){ //判断存储空间是否够用
		ElemType *newbase = (ElemType *)realloc(p->elem, (p->size + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase) return -1;//存储空间分配失败
		p->elem = newbase;//新基址
		p->size += LISTINCREMENT;//增加存储容量
	}
	ElemType *elem_q = NULL;, *elem_p = NULL;;
	elem_q = &(p->elem[index]); //q为插入位置
	for (elem_p = &(p->elem[p->length - 1]); elem_p >= elem_q; --elem_p){ //从ai到an-1依次后移，注意后移操作要从后往前进行
		*(elem_p + 1) = *elem_p;
	}
	*elem_q = *e;
	++p->length;
	return 0;
}

static int deleteElem(LinearList *This, int index, ElemType* e){
	LinearList_P *p = This->This;
	if (index<1 || index > p->length) return -1;
	ElemType *elem_q = NULL;, *elem_p = NULL;;
	elem_p = &(p->elem[index]);//elem_p为被删除元素的位置
	*e = *elem_p; //被删除的元素赋值给e
	elem_q = p->elem + p->length - 1;//elem_q指向表尾最后一个元素
	for (++elem_p; elem_p <= elem_q; ++elem_p){ //从elem_p的下一个元素开始依次前移
		*(elem_p - 1) = *elem_p;
	}
	--p->length;
	return 0;
}

static int appendElem(LinearList *This,ElemType* e){
	LinearList_P *p = This->This;
	if (p->length >= p->size){ //判断存储空间是否够用
		ElemType *newbase = (ElemType *)realloc(p->elem, (p->size + LISTINCREMENT)*sizeof(ElemType));
		if (!newbase) return -1;//存储空间分配失败
		p->elem = newbase;//新基址
		p->size += LISTINCREMENT;//增加存储容量
	}
	p->elem[p->length] = *e;
	++p->length;
	return 0;
}

static int popElem(LinearList *This, ElemType* e){
	LinearList_P *p = This->This;
	if (isEmpty(This)) return -1;
	*e = p->elem[p->length - 1];
	--p->length;
	return 0;
}

