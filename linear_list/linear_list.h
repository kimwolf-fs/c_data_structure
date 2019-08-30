/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LINEAR_LIST_H
#define __LINEAR_LIST_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef int ElemType;      //数据元素的类型，假设是int型的

typedef struct LinearList_P{
	ElemType *elem;  //存储空间的基地址
	int length;      //当前线性表的长度
	int size;    //当前分配的存储容量
}LinearList_P;

typedef struct LinearList{
	LinearList_P *This;  
	void (*clear)(struct LinearList *This);
	int (*isEmpty)(struct LinearList *This);
	int (*length)(struct LinearList *This);
	void (*print)(struct LinearList *This);
	int (*indexElem)(struct LinearList *This, ElemType* x);
	int (*priorElem)(struct LinearList *This, ElemType* cur_elem, ElemType* pre_elem);
	int (*getElem)(struct LinearList *This, int index, ElemType* e);
	int (*modifyElem)(struct LinearList *This, int index, ElemType* e);
	int (*nextElem)(struct LinearList *This, ElemType* cur_elem, ElemType* next_elem);
	int (*insertElem)(struct LinearList *This, int index, ElemType* e);
	int (*deleteElem)(struct LinearList *This, int index, ElemType* e);
	int (*appendElem)(struct LinearList *This,ElemType* e);
	int (*popElem)(struct LinearList *This, ElemType* e);
}LinearList;

/* Exported define -----------------------------------------------------------*/
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10   //线性表存储空间的分配增量(当存储空间不够时要用到)
/* Exported macro ------------------------------------------------------------*/
LinearList *InitLinearList();
void DestroyLinearList(LinearList *L);

#endif
