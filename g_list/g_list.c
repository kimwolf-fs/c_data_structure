#include <stdio.h>
#include <malloc.h>
#include "Glist.h"

static int isEmpty(GList *This);
static int length(GList *This);
static void print(GList *This);
static int getDepth(GList *This);
static int getHead(GList *This,GLNode **n);
static int getTear(GList *This,GLNode **n);
static int getGLNode(GList *This,int index,GLNode **n);
static int insertGLNode(GList *This, int index, GLNode *n);
static int insertGLNodeFront(GList *This, GLNode *n);
static int deleteGLNodeFront(GList *This);
static int insertGLNodeTear(GList *This, GLNode *n);
static int deleteGLNodeTear(GList *This);
static void traversal(GList *This,int (*visit)(GLNodeElemType **elem));

static GLNode *createGListFromString(GLNode **p,MyString *gListStr){
	int i;
	GLNode **create_temp = p;
	GLNode *glnode_temp = NULL;
	GLNode *glnode_root = NULL;
	MyString *elemstr = NULL;
	MyString *leftstr = NULL;
	MyString *substr = substrMyString(gListStr,1,gListStr->length-1);//脱去括号
	destroyMyString(gListStr);
	if(!substr){ //括号内是一个空表
		*create_temp = (GLNode*)malloc(sizeof(GLNode)); //添加原子结点
		if(*create_temp){
			(*create_temp)->tag = ATOM;
			(*create_temp)->content.elem = elemstr;
			(*create_temp)->prior = NULL;
			(*create_temp)->next = NULL;
		}
		glnode_root = *create_temp;
	}else{
		do{
			if(substr){
				if(*(substr->str) != '['){
					i = myStringIndexChar(substr,',',0);
					if(i != -1){
						elemstr = substrMyString(substr,0,i);//提取表头
						leftstr = substrMyString(substr,i+1,substr->length);//提取剩余部分
						destroyMyString(substr);
						substr = leftstr;
					}else{
						elemstr = substrMyString(substr,0,substr->length);
						destroyMyString(substr);
					}
					glnode_temp = *create_temp;
					*create_temp = (GLNode*)malloc(sizeof(GLNode)); //添加原子结点
					if(*create_temp){
						(*create_temp)->tag = ATOM;
						(*create_temp)->content.elem = elemstr;
						if(glnode_temp){
							(*create_temp)->prior = glnode_temp;
							glnode_temp->next = *create_temp;
						}else{
							(*create_temp)->prior = NULL;
							glnode_root = *create_temp;
						}
						(*create_temp)->next = NULL;
					}
				}else{
					i = getMatchingBracketIndex(substr,'[',0);
					if(i != -1){
						elemstr = substrMyString(substr,0,i+1);//提取表头,完整的一个Glist
						leftstr = substrMyString(substr,i+2,substr->length);//提取剩余部分
						destroyMyString(substr);
						substr = leftstr;
					}
					glnode_temp = *create_temp;
					*create_temp = (GLNode*)malloc(sizeof(GLNode)); //添加列表结点
					if(*create_temp){
						(*create_temp)->tag = LIST;
						if(glnode_temp){
							(*create_temp)->prior = glnode_temp;
							glnode_temp->next = *create_temp;
						}else{
							(*create_temp)->prior = NULL;
							glnode_root = *create_temp;
						}
						(*create_temp)->next = NULL;
						(*create_temp)->content.hp = NULL;
						(*create_temp)->content.hp = createGListFromString(&((*create_temp)->content.hp),elemstr);
					}
				}
			}else{
				break;
			}
		}while(i != -1);
	}
	return glnode_root;
}

GList *initGListFromString(char *listStr){
	MyString *gListStr = NULL;
	GLNode *p = NULL;
	GList *L = (GList *)malloc(sizeof(GList));
	if(!L) return NULL;
	gListStr = myStringAssign(listStr);
	if(!gListStr){
		free(L);
		return NULL;
	}
	if(*(gListStr->str) != '['){
		printf("ListStr format error\n");
		destroyMyString(gListStr);
		free(L);
		return NULL;
	}
	if(isBracketMatching(gListStr,'[') == 0){
		printf("ListStr Bracke not match\n");
		destroyMyString(gListStr);
		free(L);
		return NULL;
	}
	L->root = NULL;
	L->root = createGListFromString(&(L->root),gListStr);
	p = L->root;
	while(p->next){
		p = p->next;
	}
	L->tear = p;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->getDepth = getDepth;
	L->getHead = getHead;
	L->getTear = getTear;
	L->getGLNode = getGLNode;
	L->insertGLNode = insertGLNode;
	L->insertGLNodeFront = insertGLNodeFront;
	L->deleteGLNodeFront = deleteGLNodeFront;
	L->insertGLNodeTear = insertGLNodeTear;
	L->deleteGLNodeTear = deleteGLNodeTear;
	L->traversal = traversal;
	return L;
}

GList *initGListFromGLNode(GLNode *n){
	GLNode *p = NULL;
	GList *L = (GList *)malloc(sizeof(GList));
	if(!L) return NULL;
	L->root = NULL;
	p = copyGLNode(n);
	if(p){
		if(p->tag == ATOM){
			L->root = p;
		}else{ //脱下外层的list
			L->root = p->content.hp;
			free(p);
		}
	}
	p = L->root;
	while(p->next){
		p = p->next;
	}
	L->tear = p;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->getDepth = getDepth;
	L->getHead = getHead;
	L->getTear = getTear;
	L->getGLNode = getGLNode;
	L->insertGLNode = insertGLNode;
	L->insertGLNodeFront = insertGLNodeFront;
	L->deleteGLNodeFront = deleteGLNodeFront;
	L->insertGLNodeTear = insertGLNodeTear;
	L->deleteGLNodeTear = deleteGLNodeTear;
	L->traversal = traversal;
	return L;
}

static void printGList(GLNode *n){
	GLNode *temp = n;
	if(temp){
		if(temp->tag == ATOM){
			if(temp->content.hp){
				printf("%s",temp->content.elem->str);
			}
		}else{
			printf("[");
			printGList(temp->content.hp);
			printf("]");
		}
	}
	temp = temp->next;
	while(temp){
		if(temp->tag == ATOM){
			if(temp->content.elem){
				printf(",%s",temp->content.elem->str);
			}
		}else{
			printf(",[");
			printGList(temp->content.hp);
			printf("]");
		}
		temp = temp->next;
	}
}

static void print(GList *This){
	if(This){
		if(This->root){
			printf("[");
			printGList(This->root);
			printf("]\n");
		}
	}
}

void DestroyGList(GList *L){
	if(L){
		if(L->root){
			destroyGLNode(L->root);
		}
		free(L);
		L = NULL;
	}
}

static int isEmpty(GList *This){
	if(!This) return 1;
	if(This->root){
		return 0;
	}else{
		return 1;
	}
}

static int length(GList *This){
	int i = 0;
	if(!This) return 0;
	if(!This->root) return 0;
	GLNode *p = This->root;
	while(p){
		i++;
		p = p->next;
	}
	return i;
}

static int getGListDepth(GLNode *n){
	int max = 0;
	if(!n) return 1; // 空表深度为1
	GLNode *p = n;
	while(p){
		int dep = 0;
		if(p->tag == ATOM){
			dep = 0; //原子深度为0
		}else{
			dep = getGListDepth(p->content.hp);
		}
		if(dep > max) max = dep;
		p = p->next;
	}
	return max + 1; //非空表的深度是各类元素的深度的最大值加1
}

static int getDepth(GList *This){
	if(!This) return 0;
	return getGListDepth(This->root);
}

static GLNode *copyGListOfGLNode(GLNode *n){
	if(!n) return NULL;
	GLNode *p = n;
	GLNode *copyn = NULL;
	GLNode *copyroot = NULL;
	GLNode *temp = NULL;
	while(p){
		temp = (GLNode*)malloc(sizeof(GLNode));
		if(!temp) break;
		temp->tag = p->tag;
		temp->prior = copyn;
		if(!copyn){
			copyroot = temp;
		}else{
			copyn->next = temp;
		}
		temp->next = NULL;
		copyn = temp;
		if(p->tag == ATOM){
			if(p->content.elem){
				temp->content.elem = copyMyString(p->content.elem);
			}else{
				temp->content.elem = NULL;
			}
		}else{
			if(p->content.hp){
				temp->content.hp = copyGListOfGLNode(p->content.hp);
			}else{
				temp->content.hp = NULL;
			}
		}
		p = p->next;
	}
	return copyroot;
}

GList *copyGList(GList *L){
	if(!L) return NULL;
	GLNode *p = NULL;
	GList *temp = (GList *)malloc(sizeof(GList));
	if(!temp) return NULL;
	temp->root = copyGListOfGLNode(L->root);
	p = temp->root;
	while(p->next){
		p = p->next;
	}
	temp->tear = p;
	temp->isEmpty = isEmpty;
	temp->length = length;
	temp->print = print;
	temp->getDepth = getDepth;
	temp->getHead = getHead;
	temp->getTear = getTear;
	temp->getGLNode = getGLNode;
	temp->insertGLNode = insertGLNode;
	temp->insertGLNodeFront = insertGLNodeFront;
	temp->deleteGLNodeFront = deleteGLNodeFront;
	temp->insertGLNodeTear = insertGLNodeTear;
	temp->deleteGLNodeTear = deleteGLNodeTear;
	temp->traversal = traversal;
	return temp;
}

static int getHead(GList *This,GLNode **n){
	if(!This) return -1;
	*n = This->root;
	return 0;
}

static int getTear(GList *This,GLNode **n){
	if(!This) return -1;
	*n = This->tear;
	return 0;
}

static int getGLNode(GList *This,int index,GLNode **n){
	if(!This){
		*n = NULL;
		return -1;
	}
	int i = 0;
	GLNode *p = This->root;
	while(p && i < index){
		p = p->next;
		i++;
	}
	if(!p || i > index){
		*n = NULL;
		return -1;
	}
	*n = p;
	return 0;
}

static int insertGLNode(GList *This, int index, GLNode *n){
	if(!This) return -1;
	GLNode *newp = copyGLNode(n);
	GLNode *p = This->root;
	GLNode *temp = NULL;
	int j = 0;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index){
		destroyGLNode(temp);
		return -1;
	}
	if(p->prior){
		temp = p->prior;
		p->prior = newp;
		temp->next = newp;
		newp->prior = temp;
		newp->next = p;
	}else{
		newp->prior = NULL;
		newp->next = p;
		p->prior = newp;
		This->root = newp;
	}
	return 0;
}

static int insertGLNodeFront(GList *This, GLNode *n){
	if(!This) return -1;
	GLNode *temp = copyGLNode(n);
	if(temp){
		GLNode *p = This->root;
		This->root = temp;
		temp->prior = NULL;
		temp->next = p;
		p->prior = temp;
	}
	return 0;
}

static int deleteGLNodeFront(GList *This){
	if(!This || !This->root) return -1;
	GLNode *p = This->root;
	This->root = p->next;
	if(p->next){
		p->next->prior = NULL;
	}else{
		This->tear = NULL;
	}
	if(p->tag == ATOM){
		if(p->content.elem){
			destroyMyString(p->content.elem);
		}
	}else{
		destroyGLNode(p->content.hp);
	}
	free(p);
	return 0;
}

static int insertGLNodeTear(GList *This, GLNode *n){
	if(!This) return -1;
	GLNode *temp = copyGLNode(n);
	if(temp){
		This->tear->next = temp;
		temp->prior = This->tear;
		temp->next = NULL;
		This->tear = temp;
	}
	return 0;
}

static int deleteGLNodeTear(GList *This){
	if(!This || !This->tear) return -1;
	GLNode *p = This->tear->prior;
	if(This->tear->tag == ATOM){
		if(This->tear->content.elem){
			destroyMyString(This->tear->content.elem);
		}
	}else{
		destroyGLNode(This->tear->content.hp);
	}
	free(This->tear);
	if(p){
		p->next = NULL;
		This->tear = p;
	}else{
		This->tear = NULL;
		This->root = NULL;
	}
	return 0;
}

static void traversalGList(GLNode *n,int (*visit)(GLNodeElemType **elem)){
	if(!n) return;
	GLNode *p = n;
	while(p){
		if(p->tag == ATOM){
			if(p->content.elem){
				if(visit(&p->content.elem) != 0) break;
			}
		}else{
			traversalGList(p->content.hp,visit);
		}
		p = p->next;
	}
}

static void traversal(GList *This,int (*visit)(GLNodeElemType **elem)){
	if(!This) return;
	traversalGList(This->root,visit);
}

//*************************************************************************************************//
//单独的GLNode可用函数

void printGLNode(GLNode *n){
	if(n){
		if(n->tag == ATOM){
			if(n->content.elem){
				printf("%s\n",n->content.elem->str);
			}
		}else{
			printf("[");
			printGList(n->content.hp);
			printf("]\n");
		}
	}
}

int getGLNodeDepth(GLNode *n){
	if(!n) return 1; // 空表深度为1
	if(n->tag == ATOM){
		return 0; //原子深度为0
	}else{
		return getGListDepth(n->content.hp);
	}		
}

void destroyGLNode(GLNode *n){
	GLNode *p = n;
	GLNode *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		if(temp->tag == ATOM){
			if(temp->content.elem){
				destroyMyString(temp->content.elem);
			}
		}else{
			destroyGLNode(temp->content.hp);
		}
		free(temp);
	}
}

void traversalGLNode(GLNode *n,int (*visit)(GLNodeElemType **elem)){
	if(!n) return;
	if(n){
		if(n->tag == ATOM){
			if(n->content.elem){
				visit(&n->content.elem);
			}
		}else{
			traversalGList(n->content.hp,visit);
		}
	}
}

GLNode *copyGLNode(GLNode *n){
	if(!n) return NULL;
	GLNode *temp = (GLNode*)malloc(sizeof(GLNode));
	if(!temp) return NULL;
	temp->tag = n->tag;
	temp->prior = NULL;
	temp->next = NULL;
	if(n->tag == ATOM){
		if(n->content.elem){
			temp->content.elem = copyMyString(n->content.elem);
		}else{
			temp->content.elem = NULL;
		}
	}else{
		if(n->content.hp){
			temp->content.hp = copyGListOfGLNode(n->content.hp);
		}
	}
	return temp;
}