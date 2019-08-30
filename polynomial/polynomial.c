#include <stdio.h>
#include <malloc.h>
#include "Polynomial.h"

static void clear(Polynomial *This);
static int isEmpty(Polynomial *This);
static int length(Polynomial *This);
static void print(Polynomial *This);
static int appendElem(Polynomial *This, ElemType e);

Polynomial *InitPolynomial(){
	Polynomial *L = (Polynomial *)malloc(sizeof(Polynomial));
	Node *p = (Node *)malloc(sizeof(Node));
	L->This = p;
	p->next = NULL;
	L->clear = clear;
	L->isEmpty = isEmpty;
	L->length = length;
	L->print = print;
	L->appendElem = appendElem;
	return L;
}

Polynomial *CreatePolynomial(ElemType *params,int length){
	Polynomial *L = InitPolynomial();
	int i;
	for(i=0;i<length;i++){
		L->appendElem(L, *(params+i));
	}
	return L;
}

void DestroyPolynomial(Polynomial *L){
	L->clear(L);
	free(L->This);
	free(L);
	L = NULL;
}

static void clear(Polynomial *This){
	Node *p = This->This->next;
	Node *temp = NULL;
	while(p){
		temp = p;
		p = p->next;
		free(temp);
	} 
	p = This->This;
	p->next = NULL;
}

static int isEmpty(Polynomial *This){
	Node *p = This->This;
	if(p->next){
		return 0;
	}else{
		return 1;
	}
}

static int length(Polynomial *This){
	int j = 0;
	Node *p = This->This->next;
	while(p){
		j++;
		p = p->next;
	} 
	return j;
}

static void print(Polynomial *This){
	Node *p = This->This->next;
	if(p){
		printf("%fx^%f", p->elem.coefficient,p->elem.exponent);
		p = p->next;
	}
	while(p){
		printf(" + %fx^%f", p->elem.coefficient,p->elem.exponent);
		p = p->next;
	} 
	printf("\n");
}

static int appendElem(Polynomial *This, ElemType e){
	Node *p = This->This;
	Node *temp = (Node *)malloc(sizeof(Node));
	if(!temp) return -1;
	while(p){
		if(NULL == p->next){
			temp->elem.coefficient = e.coefficient;
			temp->elem.exponent = e.exponent;
			p->next = temp;
			temp->next =  NULL;
		}
		p = p->next;
	} 
	return 0;
}

Polynomial *addPolynomial(Polynomial *pa,Polynomial *pb){
	Polynomial *L = InitPolynomial();
	ElemType a,b,sum;
	Node *ha = pa->This->next;
	Node *hb = pb->This->next;
	while(ha&&hb){
		a = ha->elem;
		b = hb->elem;
		if(a.exponent > b.exponent){
			L->appendElem(L, b);
			hb = hb->next;
		}else if(a.exponent == b.exponent){
			sum.exponent = a.exponent;
			sum.coefficient = a.coefficient + b.coefficient;
			if(sum.coefficient != 0){
				L->appendElem(L, sum);
			}
			ha = ha->next;
			hb = hb->next;
		}else{
			L->appendElem(L, a);
			ha = ha->next;
		}
	}
	while(ha){
		a = ha->elem;
		L->appendElem(L, a);
		ha = ha->next;
	}
	while(hb){
		b = hb->elem;
		L->appendElem(L, b);
		hb = hb->next;
	}
	return L;
}

Polynomial *subPolynomial(Polynomial *pa,Polynomial *pb){
	Polynomial *L = InitPolynomial();
	ElemType a,b,sub;
	Node *ha = pa->This->next;
	Node *hb = pb->This->next;
	while(ha&&hb){
		a = ha->elem;
		b = hb->elem;
		if(a.exponent > b.exponent){
			sub.exponent = b.exponent;
			sub.coefficient = -b.coefficient;
			L->appendElem(L, sub);
			hb = hb->next;
		}else if(a.exponent == b.exponent){
			sub.exponent = a.exponent;
			sub.coefficient = a.coefficient - b.coefficient;
			if(sub.coefficient != 0){
				L->appendElem(L, sub);
			}
			ha = ha->next;
			hb = hb->next;
		}else{
			L->appendElem(L, a);
			ha = ha->next;
		}
	}
	while(ha){
		a = ha->elem;
		L->appendElem(L, a);
		ha = ha->next;
	}
	while(hb){
		b = hb->elem;
		sub.exponent = b.exponent;
		sub.coefficient = -b.coefficient;
		L->appendElem(L, sub);
		hb = hb->next;
	}
	return L;
}

Polynomial *kMulPolynomial(Polynomial *pa,ElemType a){
	Polynomial *L = InitPolynomial();
	Node *ha = pa->This->next;
	ElemType temp;
	while(ha){
		temp.exponent = ha->elem.exponent + a.exponent;
		temp.coefficient = ha->elem.coefficient * a.coefficient;
		L->appendElem(L, temp);
		ha = ha->next;
	}
	return L;
}

Polynomial *mulPolynomial(Polynomial *pa,Polynomial *pb){
	Polynomial *temp = InitPolynomial();
	Polynomial *temp1 = NULL,*temp2 = NULL;
	Node *hb = pb->This->next;
	while(hb){
		temp1 = kMulPolynomial(pa,hb->elem);
		temp2 = addPolynomial(temp1,temp);
		DestroyPolynomial(temp1);	
		DestroyPolynomial(temp);
		temp = temp2;
		hb = hb->next;
	}
	return temp;
}
