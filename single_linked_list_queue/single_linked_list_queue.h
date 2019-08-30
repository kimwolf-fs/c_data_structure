/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SINGLELINKEDLISTQUEUE_H
#define _SINGLELINKEDLISTQUEUE_H
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

typedef struct SingleLinkedListQueue{
	QNode *This;
	Queueptr front; //队头
	Queueptr tear; //队尾
	void (*clear)(struct SingleLinkedListQueue *This);
	int (*isEmpty)(struct SingleLinkedListQueue *This);
	int (*length)(struct SingleLinkedListQueue *This);
    QNode *(*getHead)(struct SingleLinkedListQueue *This);
	int (*enQueue)(struct SingleLinkedListQueue *This,QNode *n);
	int (*deQueue)(struct SingleLinkedListQueue *This,QNode *n);
	int (*traverse)(struct SingleLinkedListQueue *This,int (*visit)(QNode *n));
}SingleLinkedListQueue;

/* Exported macro ------------------------------------------------------------*/
SingleLinkedListQueue *InitSingleLinkedListQueue();
void DestroySingleLinkedListQueue(SingleLinkedListQueue *Q);

#endif