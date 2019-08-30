/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _DLLQUEUE_H
#define _DLLQUEUE_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct DLLQNode{
	void *elem;
	struct DLLQNode *prior;
	struct DLLQNode *next;
}DLLQNode;

typedef struct DLLQueue{
	DLLQNode *front;
	DLLQNode *tear;
	void (*clear)(struct DLLQueue *This);
	int (*isEmpty)(struct DLLQueue *This);
	int (*length)(struct DLLQueue *This);
	void (*riseTraverse)(struct DLLQueue *This,int (*visit)(void **e));
	void (*downTraverse)(struct DLLQueue *This,int (*visit)(void **e));
	int (*getHead)(struct DLLQueue *This, void **e);
	int (*enQueue)(struct DLLQueue *This, void *e);
	int (*deQueue)(struct DLLQueue *This, void **e);
}DLLQueue;

/* Exported macro ------------------------------------------------------------*/
DLLQueue *InitDLLQueue();
void DestroyDLLQueue(DLLQueue *Q);

#endif