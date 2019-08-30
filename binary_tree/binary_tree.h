/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BINARYTREE_H
#define __BINARYTREE_H
/* Includes ------------------------------------------------------------------*/
#include "ElemTypeDefine.h"
/* Exported types ------------------------------------------------------------*/

typedef enum BinaryTreeOrder{
	preOrder, //前序
	inOrder, //中序
	postOrder //后序
}BinaryTreeOrder;

typedef struct BiTNode{
	void *elem;
	struct BiTNode *parent;
	struct BiTNode *left;
	struct BiTNode *right;
}BiTNode;

typedef struct BinaryTree{
	BiTNode *Root;  
	int length;
	void (*clear)(struct BinaryTree *This);
	int (*isEmpty)(struct BinaryTree *This);
}BinaryTree;

BinaryTree *InitBinaryTree();
void DestroyBinaryTree(BinaryTree *T);

#endif
