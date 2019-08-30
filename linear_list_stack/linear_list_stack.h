/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LINEARLISTSTACK_H
#define __LINEARLISTSTACK_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef char ElemType;

typedef struct LinearListStack_P{
	ElemType *base;  
	ElemType *top;   //栈顶指针
	int length;      //当前线性表栈的长度
	int size;    //当前分配的存储容量
}LinearListStack_P;

typedef struct LinearListStack{
	LinearListStack_P *This;  
	void (*clear)(struct LinearListStack *This);
	int (*isEmpty)(struct LinearListStack *This);
	int (*length)(struct LinearListStack *This);
	void (*risePrint)(struct LinearListStack *This);
	void (*downPrint)(struct LinearListStack *This);
	int (*getTop)(struct LinearListStack *This,ElemType* e);
	int (*push)(struct LinearListStack *This,ElemType* e);
	int (*pop)(struct LinearListStack *This, ElemType* e);
}LinearListStack;

/* Exported define -----------------------------------------------------------*/
#define STACK_INIT_SIZE 100 //线性表栈存储空间的初始分配量
#define STACKINCREMENT 10   //线性表栈存储空间的分配增量(当存储空间不够时要用到)
/* Exported macro ------------------------------------------------------------*/
LinearListStack *InitLinearListStack();
void DestroyLinearListStack(LinearListStack *L);

#endif
