#include <stdio.h>
#include <malloc.h>
#include "MyStringArray.h"

static void clear(MyStringArray *This);
static int isEmpty(MyStringArray *This);
static int length(MyStringArray *This);
static int index(MyStringArray *This, MyString *e);
static int get(MyStringArray *This, int index, MyString **e);
static int getFront(MyStringArray *This, MyString **e);
static int getTear(MyStringArray *This, MyString **e);
static int modify(MyStringArray *This, int index, MyString *e);
static int insert(MyStringArray *This, int index, MyString *e);
static int delete(MyStringArray *This, int index, MyString **e);
static int tearPush(MyStringArray *This, MyString *e);
static int tearPop(MyStringArray *This, MyString **e);
static int frontPush(MyStringArray *This, MyString *e);
static int frontPop(MyStringArray *This, MyString **e);
static int traverse(MyStringArray *This,int (*visit)(MyString **e));

MyStringArray *InitMyStringArray(){
	MyStringArray *strArray = (MyStringArray *)malloc(sizeof(MyStringArray));
	MyStringArray_P *p = (MyStringArray_P *)malloc(sizeof(MyStringArray_P));
	strArray->This = p;
	p->next = NULL;
	strArray->front = p;
	strArray->tear = strArray->front;
	strArray->clear = clear;
	strArray->isEmpty = isEmpty;
	strArray->length = length;
	strArray->index = index;
	strArray->get = get;
	strArray->getFront = getFront;
	strArray->getTear = getTear;
	strArray->modify = modify;
	strArray->insert = insert;
	strArray->delete = delete;
	strArray->tearPush = tearPush;
	strArray->tearPop = tearPop;
	strArray->frontPush = frontPush;
	strArray->frontPop = frontPop;
	strArray->traverse = traverse;
	return strArray;
}

void DestroyMyStringArray(MyStringArray *strArray){
	strArray->clear(strArray);
	free(strArray->This);
	strArray->This = NULL;
	free(strArray);
	strArray = NULL;
}

static void clear(MyStringArray *This){
	MyStringArray_P *p = This->This->next;
	MyStringArray_P *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp->mystring->str);
		temp->mystring->str = NULL;
		free(temp);
		temp = NULL;
	} 
	p = This->This;
	p->next = NULL;
	This->front = p;
	This->tear = This->front;
}

static int isEmpty(MyStringArray *This){
	MyStringArray_P *p = This->This;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(MyStringArray *This){
	int j = 0;
	MyStringArray_P *p = This->This->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static int index(MyStringArray *This, MyString *e){
	MyStringArray_P *p = This->This->next;
	int pos = -1;
	int j = 0;
	if(!e) return -1;
	while(p){
		if(compareMyString(p->mystring,e) == 0){
			pos = j;
		}
		p = p->next;
		j++;
	} 
	return pos;
}

static int get(MyStringArray *This, int index, MyString **e){
	MyStringArray_P *p = This->This->next;
	int j = 0;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	*e = copyMyString(p->mystring);
	return 0;
}

static int getFront(MyStringArray *This, MyString **e){
	MyStringArray_P *p = This->front->next;
	*e = copyMyString(p->mystring);
	return 0;
}

static int getTear(MyStringArray *This, MyString **e){
	MyStringArray_P *p = This->tear;
	*e = copyMyString(p->mystring);
	return 0;
}

static int modify(MyStringArray *This, int index, MyString *e){
	MyStringArray_P *p = This->This->next;
	if(!e) return -1;
	int j = 0;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	free(p->mystring);
	p->mystring = copyMyString(e);
	if(p->mystring){
		return 0;
	}else{
		return -1;
	}
}

static int insert(MyStringArray *This, int index, MyString *e){
	MyStringArray_P *p = This->This;
	int j = 0;
	if(!e) return -1;
	MyStringArray_P *temp = (MyStringArray_P *)malloc(sizeof(MyStringArray_P));
	if(!temp) return -1;
	while(p && j < index){
		p = p->next;
		j++;
	} 
	if(!p || j > index) return -1;
	temp->next = p->next;
	p->next = temp;
	temp->mystring = copyMyString(e);
	if(!temp->mystring){
		free(temp);
		return -1;
	}else{
		return 0;
	}
}

static int delete(MyStringArray *This, int index, MyString **e){
	MyStringArray_P *p = This->This;
	MyStringArray_P *temp = NULL;
	int j = 0;
	while(p->next && j < index){
		p = p->next;
		j++;
	} 
	if(!p->next || j > index) return -1;
	temp = p->next;
	p->next = temp->next;
	*e = copyMyString(temp->mystring);
	free(temp);
	return 0;
}

static int tearPush(MyStringArray *This, MyString *e){
	MyStringArray_P *p = This->This;
	if(!e) return -1;
	MyStringArray_P *temp = (MyStringArray_P *)malloc(sizeof(MyStringArray_P));
	if(!temp) return -1;
	temp->mystring = copyMyString(e);
	if(temp->mystring){
		if(This->front == This->tear){
			p->next = temp;
		}else{
			This->tear->next = temp;
		}
		temp->next = NULL;
		This->tear = temp;
		return 0;
	}else{
		free(temp);
		return -1;
	}
}

static int tearPop(MyStringArray *This, MyString **e){
	MyStringArray_P *p = This->This;
	MyStringArray_P *temp = NULL;
	while(p->next->next){
		p = p->next;
	} 
	temp = p->next;
	This->tear = p;
	if(!temp) return -1;
	*e = copyMyString(temp->mystring);
	free(temp);
	p->next = NULL;
	return 0;
}

static int frontPush(MyStringArray *This, MyString *e){
	MyStringArray_P *p = This->This;
	if(!e) return -1;
	MyStringArray_P *temp = (MyStringArray_P *)malloc(sizeof(MyStringArray_P));
	if(!temp) return -1;
	temp->mystring = copyMyString(e);
	if(temp->mystring){
		temp->next = p->next;
		p->next = temp;
		if(This->front == This->tear){
			This->tear = temp;
		}
		return 0;
	}else{
		free(temp);
		return -1;
	}
}

static int frontPop(MyStringArray *This, MyString **e){
	if(This->front == This->tear){
		e = NULL;
		return -1;
	}
	MyStringArray_P *p = This->front->next;
	*e = copyMyString(p->mystring);
	This->front->next = p->next; 
	if(This->tear == p) This->tear = This->front;
	free(p);
	return 0;
}

static int traverse(MyStringArray *This,int (*visit)(MyString **e)){
	if(This->front == This->tear){
		return -1;
	}
	MyStringArray_P *temp = This->front->next;
	while(temp){
		if(visit(&(temp->mystring)) != 0) break;
		temp = temp->next;
	} 
	return 0;
}

