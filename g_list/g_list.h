/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GLIST_H
#define _GLIST_H

#include "MyString.h"

typedef MyString GLNodeElemType;

typedef enum GLNodeElemTag{
	ATOM,  //原子结点
	LIST   //表结点
}GLNodeElemTag;

typedef struct GLNode{
	GLNodeElemTag tag;   //tag用于区分原子结点和表结点
	union content{              //原子结点和表结点的联合
		GLNodeElemType *elem;  //原子结点的指针
		struct GLNode *hp; //表结点的表头指针
	}content;
	struct GLNode *prior; //指向前一个元素的结点 
	struct GLNode *next; //指向下一个元素的结点 
}GLNode;

typedef struct GList{
	GLNode *root;
	GLNode *tear;
	int (*isEmpty)(struct GList *This);
	int (*length)(struct GList *This);
	void (*print)(struct GList *This);
	int (*getDepth)(struct GList *This);
	int (*getHead)(struct GList *This,GLNode **n);
	int (*getTear)(struct GList *This,GLNode **n);
	int (*getGLNode)(struct GList *This,int index,GLNode **n);
	int (*insertGLNode)(struct GList *This, int index, GLNode *n);
	int (*insertGLNodeFront)(struct GList *This, GLNode *n);
	int (*deleteGLNodeFront)(struct GList *This);
	int (*insertGLNodeTear)(struct GList *This, GLNode *n);
	int (*deleteGLNodeTear)(struct GList *This);
	void (*traversal)(struct GList *This,int (*visit)(GLNodeElemType **elem));
}GList;

GList *initGListFromString(char *listStr);
GList *initGListFromGLNode(GLNode *n);
GList *copyGList(GList *L);
void DestroyGList(GList *L);

void printGLNode(GLNode *n);
int getGLNodeDepth(GLNode *n);
GLNode *copyGLNode(GLNode *n);
void traversalGLNode(GLNode *n,int (*visit)(GLNodeElemType **elem));
void destroyGLNode(GLNode *n);


#endif