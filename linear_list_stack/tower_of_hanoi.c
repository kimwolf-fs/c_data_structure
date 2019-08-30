#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

void hanoi(int n,LinearListStack *x,LinearListStack *y,LinearListStack *z){
	char elem;
	if(n == 1){
		x->pop(x,&elem);
		z->push(z,&elem); //将编号为1的圆盘从x移到z
		//******************************打印步骤需要，非执行过程*********************
		printf("move %c from %c to %c\n",elem,*(x->This->base),*(z->This->base));
		x->risePrint(x);
		y->risePrint(y);
		z->risePrint(z);
		printf("\n");
		//***************************************************************************
	}else{
		hanoi(n-1,x,z,y);//将x上编号为1至n-1的圆盘移到y，z做辅助塔
		x->pop(x,&elem);
		z->push(z,&elem);//将编号为n的圆盘从x移到z
		//******************************打印步骤需要，非执行过程*********************
		printf("move %c from %c to %c\n",elem,*(x->This->base),*(z->This->base));
		x->risePrint(x);
		y->risePrint(y);
		z->risePrint(z);
		printf("\n");
		//***************************************************************************
		hanoi(n-1,y,x,z);//将y上编号为1至n-1的圆盘移到z，x做辅助塔
	}
}

int main(void)
{
	int i;
	char elem;
	LinearListStack *x = InitLinearListStack();
	LinearListStack *y = InitLinearListStack();
	LinearListStack *z = InitLinearListStack();
	elem = 'x';
	x->push(x,&elem);
	elem = ':';
	x->push(x,&elem);
	elem = 'y';
	y->push(y,&elem);
	elem = ':';
	y->push(y,&elem);
	elem = 'z';
	z->push(z,&elem);
	elem = ':';
	z->push(z,&elem);
	for(i=9;i>0;i--){
		elem = i+0x30;
		x->push(x,&elem);
	}
	hanoi(9,x,y,z);
	DestroyLinearListStack(x);
	DestroyLinearListStack(y);
	DestroyLinearListStack(z);
	return 0;
}