/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SINGLECIRCULARLINKEDLISTQUEUE_H
#define _SINGLECIRCULARLINKEDLISTQUEUE_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct QElemType{
	int id;
	char name[20];
}QElemType;     

typedef struct QNode{
	QElemType elem;  //存储空间
	struct QNode *next;
}QNode,*Queueptr;

typedef struct SingleCircularLinkedListQueue{
	QNode *This;
	Queueptr front; //队头
	Queueptr tear; //队尾
	void (*clear)(struct SingleCircularLinkedListQueue *This);
	int (*isEmpty)(struct SingleCircularLinkedListQueue *This);
	int (*length)(struct SingleCircularLinkedListQueue *This);
    QNode *(*getHead)(struct SingleCircularLinkedListQueue *This);
	int (*enQueue)(struct SingleCircularLinkedListQueue *This,QNode *n);
	int (*deQueue)(struct SingleCircularLinkedListQueue *This,QNode *n);
	int (*traverse)(struct SingleCircularLinkedListQueue *This,int (*visit)(QNode *n),int circular);
}SingleCircularLinkedListQueue;

/* Exported macro ------------------------------------------------------------*/
SingleCircularLinkedListQueue *InitSingleCircularLinkedListQueue();
void DestroySingleCircularLinkedListQueue(SingleCircularLinkedListQueue *Q);

#endif