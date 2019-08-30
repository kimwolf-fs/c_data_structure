#include <stdio.h>
#include <malloc.h>
#include "MyStringArray.h"

char name[][14] = {"without ","new ","experiences, ","something ","inside ","of ","us ","sleeps."};

int printMyString(MyString **str){
	printf("%s",(*str)->str);
	return 0;
}

int main(void){
	int i;
	MyStringArray *strarray = InitMyStringArray();
	MyString *string = NULL;
	printf("MyStringArray is empty:%d\n",strarray->isEmpty(strarray));
	for(i=0;i<8;i++){
		string = myStringAssign(name[i]);
		strarray->frontPush(strarray,string);
		destroyMyString(string);
	}

	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");
	printf("MyStringArray is empty:%d\n",strarray->isEmpty(strarray));
	printf("MyStringArray length:%d\n",strarray->length(strarray));

	strarray->clear(strarray);
	printf("MyStringArray is empty:%d\n",strarray->isEmpty(strarray));
	printf("MyStringArray length:%d\n",strarray->length(strarray));

	for(i=0;i<8;i++){
		string = myStringAssign(name[i]);
		strarray->tearPush(strarray,string);
		destroyMyString(string);
	}

	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");

	strarray->get(strarray,3,&string);
	printf("the MyString of index 3 is: ");
	printMyString(&string);
	printf("\n");
	destroyMyString(string);

	strarray->getTear(strarray,&string);
	printf("the tear MyString is: ");
	printMyString(&string);
	printf(" ,index is: %d\n",strarray->index(strarray,string));
	destroyMyString(string);

	strarray->getFront(strarray,&string);
	printf("the front MyString is: ");
	printMyString(&string);
	printf("\n");
	destroyMyString(string);

	string = myStringAssign("me ");
	strarray->modify(strarray,6,string);
	destroyMyString(string);
	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");

	string = myStringAssign("you and ");
	strarray->insert(strarray,6,string);
	destroyMyString(string);
	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");

	strarray->delete(strarray,6,&string);
	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");
	printMyString(&string);
	printf(" deleted!\n");
	destroyMyString(string);

	strarray->tearPop(strarray,&string);
	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");
	printMyString(&string);
	printf(" tear poped!\n");
	destroyMyString(string);	

	strarray->frontPop(strarray,&string);
	printf("MyStringArray: ");
	strarray->traverse(strarray,printMyString);
	printf("\n");
	printMyString(&string);
	printf(" front poped!\n");
	destroyMyString(string);	

	DestroyMyStringArray(strarray);
	return 0;
}