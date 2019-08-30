#include <stdio.h>
#include <malloc.h>
#include "Glist.h"

int visitGLNode(GLNodeElemType **elem){
	printMyString(*elem);
	return 0;
}

int main(void){
	GLNode *node1 = NULL;
	GLNode *node2 = NULL;
	GList *L = initGListFromString("[1D,2AD,[3SFDS,[4FEF,[5GRG,[6HJJY,[]]],7TKU],8GRGRH],9YJRDFB]");
	GList *L2 = NULL;
	GList *L3 = NULL;
	
	printf("list L:\n");
	L->print(L);
	printf("is list L empty:%d\n",L->isEmpty(L));
	printf("list L length:%d\n",L->length(L));
	printf("list L depth:%d\n",L->getDepth(L));
	
	printf("the index 3 of list L is : ");
	L->getGLNode(L,3,&node1);
	printGLNode(node1);
	printf("\n");
	
	printf("get glnode of index 2 of L:\n");
	L->getGLNode(L,2,&node1);
	printGLNode(node1);
	printf("\n");
	
	L2 = initGListFromGLNode(node1);
	printf("list L2:\n");
	L2->print(L2);
	printf("is list L2 empty:%d\n",L2->isEmpty(L2));
	printf("list L2 length:%d\n",L2->length(L2));
	printf("list L2 depth:%d\n",L2->getDepth(L2));
	printf("the index 0 of list L2 is : ");
	L2->getGLNode(L2,0,&node2);
	printGLNode(node2);
	printf("\n");
	
	L2->insertGLNodeFront(L2,node1);
	printf("insertGLNodeFront list L2:\n");
	L2->print(L2);
	printf("\n");
	
	L2->insertGLNodeTear(L2,node1);
	printf("insertGLNodeTear list L2:\n");
	L2->print(L2);
	printf("\n");
	
	printf("get glnode of index 0 of L2:\n");
	L2->getGLNode(L2,0,&node2);
	printGLNode(node2);
	printf("\n");
	
	printf("get glnode of index 1 of L2:\n");
	L2->getGLNode(L2,1,&node2);
	printGLNode(node2);
	printf("\n");
	
	printf("get head of L2:\n");
	L2->getHead(L2,&node2);
	printGLNode(node2);
	printf("\n");
	
	printf("get tear of L2:\n");
	L2->getTear(L2,&node2);
	printGLNode(node2);
	printf("\n");
	
	L2->deleteGLNodeTear(L2);
	printf("list L2:\n");
	L2->print(L2);
	printf("get tear of L2:\n");
	L2->getTear(L2,&node2);
	printGLNode(node2);
	printf("\n");
	
	L2->deleteGLNodeFront(L2);
	L2->deleteGLNodeFront(L2);
	printf("list L2:\n");
	L2->print(L2);
	printf("get head of L2:\n");
	L2->getHead(L2,&node2);
	printGLNode(node2);
	printf("\n");
	
	L3 = copyGList(L2);
	printf("list L3:\n");
	L3->print(L3);
	
	L3->insertGLNodeTear(L3,node1);
	printf("insertGLNodeTear list L3:\n");
	L3->print(L3);
	printf("\n");
	
	L3->insertGLNodeFront(L3,node2);
	printf("insertGLNodeFront list L3:\n");
	L3->print(L3);
	printf("\n");
	
	while(L3->length(L3)){
		printf("get tear of L3:\n");
		L3->getTear(L3,&node2);
		printGLNode(node2);
		printf("\n");
		
		L3->deleteGLNodeTear(L3);
		printf("list L3:\n");
		L3->print(L3);
		printf("\n");
	}
	
	printf("is list L3 empty:%d\n",L3->isEmpty(L3));
	printf("\n");
	
	printf("list L2:\n");
	L2->print(L2);
	printf("\n");
	
	while(L2->length(L2)){
		printf("get head of L2:\n");
		L2->getHead(L2,&node2);
		printGLNode(node2);
		printf("\n");
		
		L2->deleteGLNodeFront(L2);
		printf("list L2:\n");
		L2->print(L2);
		printf("\n");
	}
	
	printf("is list L2 empty:%d\n",L2->isEmpty(L2));
	printf("\n");
	
	printf("node1 traversal\n");
	traversalGLNode(node1,visitGLNode);
	printf("\n");
	
	printf("list L traversal\n");
	L->traversal(L,visitGLNode);
	printf("\n");
	
	DestroyGList(L);
	DestroyGList(L2);
	DestroyGList(L3);
	return 0;
}