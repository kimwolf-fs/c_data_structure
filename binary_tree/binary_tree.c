#include <stdio.h>
#include <malloc.h>
#include "BinaryTree.h"
#include "DLLStack.h"
//二叉树

BinaryTree *InitBinaryTree(){
	BinaryTree *T = (BinaryTree *)malloc(sizeof(BinaryTree));
	if(!T) return NULL;
	BiTNode *n = (BiTNode *)malloc(sizeof(BiTNode));
	T->This = n;
	return T;
}

static void clearBiTNode(BiTNode *T,int (*destroyElem)(void **elem)){
	if(!T){
		clearBiTNode(T->left,destroyElem);
		clearBiTNode(T->right,destroyElem);
		if()
		if(visit(&T) != 0) return;
	}
}

void DestroyBinaryTree(BinaryTree *T){
	if(T){
		if(T->This){
			if(T->This->elem){
				free(T->This->elem);
			}
			free(T->This);
		}
		free(T);
		L = NULL;
	}
}

//递归前序遍历
static void preOrderTraversal(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T){
		if(visit(&T) != 0) return;
		preOrderTraversal(T->left,visit);
		preOrderTraversal(T->right,visit);
	}
}

//递归中序遍历
static void inOrderTraversal(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T){
		inOrderTraversal(T->left,visit);
		if(visit(&T) != 0) return;
		inOrderTraversal(T->right,visit);
	}
}

//递归后序遍历
static void postOrderTraversal(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T){
		postOrderTraversal(T->left,visit);
		postOrderTraversal(T->right,visit);
		if(visit(&T) != 0) return;
	}
}

//非递归前序遍历
static void preOrderTraversal2(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T) return;
	DLLStack *BiTreeStack = InitDLLStack();
	BiTNode *p = T;
	while(p || !BiTreeStack->isEmpty(BiTreeStack)){ //p不空或者栈不空
		if(!p){
			BiTreeStack->pushElem(BiTreeStack,p); //存入栈中
			if(visit(&p) != 0) break;
			p = p->left; //遍历左子树
		}
		else{
			BiTreeStack->popElem(BiTreeStack,(void **)&p); //退栈
			p = p->right; //遍历右子树
		}
	}
	DestroyDLLStack(BiTreeStack);
}

//非递归中序遍历
static void inOrderTraversal2(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T) return;
	DLLStack *BiTreeStack = InitDLLStack();
	BiTNode *p = T;
	while(p || !BiTreeStack->isEmpty(BiTreeStack)){ //p不空或者栈不空
		if(!p){
			BiTreeStack->pushElem(BiTreeStack,p); //存入栈中
			p = p->left; //遍历左子树
		}
		else{
			BiTreeStack->popElem(BiTreeStack,(void **)&p); //退栈
			if(visit(&p) != 0) break;
			p = p->right; //遍历右子树
		}
	}
	DestroyDLLStack(BiTreeStack);
}

//非递归后序遍历
static void postOrderTraversal2(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T) return;
	DLLStack *BiTreeStack = InitDLLStack();
	BiTNode *p = T;
	BiTNode *pre = NULL;//前一次访问的结点
	BiTreeStack->pushElem(BiTreeStack,p); //存入栈中
	while(!BiTreeStack->isEmpty(BiTreeStac)){ //栈不空
		S->getTopElem(S,&p);
		if((p->left == NULL && p->right == NULL) || //如果当前节点没有子节点或
		(pre != NULL && (pre == p->left || pre == p->right))) //子节点都已被访问过
		{
			if(visit(&p) != 0) break;
			BiTreeStack->popElem(BiTreeStack,(void **)&p); //退栈
			pre = p;
		}
		else{
			if(p->right != NULL){
				BiTreeStack->pushElem(BiTreeStack,p->right); //先将右子树存入栈中
			}
			if(p->left != NULL){
				BiTreeStack->pushElem(BiTreeStack,p->left); //再将左子树存入栈中
			}
		}
	}
	DestroyDLLStack(BiTreeStack);
}

//递归遍历
static void depthFirstTraversal(BinaryTree *T,int (*visit)(BiTNode **T),BinaryTreeOrder binTreeOrder){
	if(!T) return;
	switch(binTreeOrder){
		case preOrder:
			preOrderTraversal(T->Root,visit);
			break;
		case inOrder:
			inOrderTraversal(T->Root,visit);
			break;
		case postOrder:
			postOrderTraversal(T->Root,visit);
			break;
	}
}

//非递归遍历
static void depthFirstTraversal2(BinaryTree *T,int (*visit)(BiTNode **T),BinaryTreeOrder binTreeOrder){
	if(!T) return;
	switch(binTreeOrder){
		case preOrder:
			preOrderTraversal2(T->Root,visit);
			break;
		case inOrder:
			inOrderTraversal2(T->Root,visit);
			break;
		case postOrder:
			postOrderTraversal2(T->Root,visit);
			break;
	}
}

//广度优先遍历
static void breadthFirstTraversal(BiTNode *T,int (*visit)(BiTNode **T)){
	if(!T || !T->Root) return;
	DLLQueue *BiTreeQueue = InitDLLQueue();
	BiTNode *p = NULL;
	BiTreeQueue->enQueue(BiTreeQueue,T->Root);
	while(!BiTreeQueue->isEmpty(BiTreeQueue)){ //队列不空
		BiTreeQueue->deQueue(BiTreeQueue,(void **)&p);
		if(visit(&p) != 0) break;
		if(p->left){
			BiTreeQueue->enQueue(BiTreeQueue,p->left);  //先将左子树入队
		}
		if(p->right){
			BiTreeQueue->enQueue(BiTreeQueue,p->right); //再将右子树入队
		}
	}
	DestroyDLLQueue(BiTreeQueue);
}
