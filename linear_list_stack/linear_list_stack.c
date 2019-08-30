#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"
//线性表栈

static void clear(LinearListStack *This);
static int isEmpty(LinearListStack *This);
static int length(LinearListStack *This);
static void risePrint(LinearListStack *This);
static void downPrint(LinearListStack *This);
static int getTop(LinearListStack *This,ElemType* e);
static int push(LinearListStack *This,ElemType* e);
static int pop(LinearListStack *This, ElemType* e);

LinearListStack *InitLinearListStack(){
	LinearListStack *L = (LinearListStack *)malloc(sizeof(LinearListStack));
	LinearListStack_P *p = (LinearListStack_P *)malloc(sizeof(LinearListStack_P));
	p->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	p->top = p->base;
	p->length = 0; //当前长度
	p->size = STACK_INIT_SIZE; //当前分配量
	L->This = p;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->risePrint = risePrint;
	L->downPrint = downPrint;
	L->getTop = getTop;
	L->push = push;
	L->pop = pop;
	return L;
}

void DestroyLinearListStack(LinearListStack *L){
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(LinearListStack *This){
	LinearListStack_P *p = This->This;
	p->top = p->base;
	p->length = 0; //当前长度
}

static int isEmpty(LinearListStack *This){
	LinearListStack_P *p = This->This;
	return (p->length == 0);
}

static int length(LinearListStack *This){
	LinearListStack_P *p = This->This;
	return p->length;
}

static void risePrint(LinearListStack *This){
	LinearListStack_P *p = This->This;
	int i;
	for (i=0; i < p->length; i++){
		printf("%c", *(p->base + i));
	}
	printf("\n");
}

static void downPrint(LinearListStack *This){
	LinearListStack_P *p = This->This;
	int i;
	for (i=0; i < p->length; i++){
		printf("%c", *(p->top - 1 - i));
	}
	printf("\n");
}

static int getTop(LinearListStack *This,ElemType* e){
	LinearListStack_P *p = This->This;
	if (p->top == p->base) return -1;
	*e = *(p->top-1);
	return 0;
}

static int push(LinearListStack *This,ElemType* e){
	LinearListStack_P *p = This->This;
	if (p->top - p->base >= p->size){ //判断存储空间是否够用
		ElemType *newbase = (ElemType *)realloc(p->base, (p->size + STACKINCREMENT)*sizeof(ElemType));
		if (!newbase) return -1;//存储空间分配失败
		p->base = newbase;//新基址
		p->top = p->base + p->size;
		p->size += STACKINCREMENT;//增加存储容量
	}
	*((p->top)++) = *e;
	++p->length;
	return 0;
}

static int pop(LinearListStack *This, ElemType* e){
	LinearListStack_P *p = This->This;
	if (p->top == p->base) return -1;
	*e = *(p->top-1);
	p->top--;
	p->length--;
	return 0;
}

