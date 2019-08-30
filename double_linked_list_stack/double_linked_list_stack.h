/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DLLSTACK_H
#define _DLLSTACK_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct DLLSNode{
	void *elem;
	struct DLLSNode *prior;
	struct DLLSNode *next;
}DLLSNode;

typedef struct DLLStack{
	DLLSNode *front;
	DLLSNode *tear;
	void (*clear)(struct DLLStack *This);
	int (*isEmpty)(struct DLLStack *This);
	int (*length)(struct DLLStack *This);
	void (*riseTraverse)(struct DLLStack *This,int (*visit)(void **e));
	void (*downTraverse)(struct DLLStack *This,int (*visit)(void **e));
	int (*getTopElem)(struct DLLStack *This, void **e);
	int (*pushElem)(struct DLLStack *This, void *e);
	int (*popElem)(struct DLLStack *This, void **e);
}DLLStack;

/* Exported macro ------------------------------------------------------------*/
DLLStack *InitDLLStack();
void DestroyDLLStack(DLLStack *S);

#endif