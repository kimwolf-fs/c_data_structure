#include <stdio.h>
#include <malloc.h>
#include "Polynomial.h"

int main(void){
	//7+3x+9X^8+5x^17
	ElemType params_a[4]={{7,0},{3,1},{9,8},{5,17}};
	//8x+22x^7+-9x^8
	ElemType params_b[3]={{8,1},{22,7},{-9,8}};
	Polynomial *pa = CreatePolynomial(params_a,4);
	Polynomial *pb = CreatePolynomial(params_b,3);
	Polynomial *sum_ab = NULL;,*sub_ab = NULL;,*mul_ab = NULL;,*kmul_a = NULL;;
	printf("pa = ");
	pa->print(pa);
	printf("pb = ");
	pb->print(pb);
	sum_ab = addPolynomial(pa,pb);
	printf("pa + pb = ");
	sum_ab->print(sum_ab);
	sub_ab = subPolynomial(pa,pb);
	printf("pa - pb = ");
	sub_ab->print(sub_ab);
	mul_ab = mulPolynomial(pa,pb);
	printf("pa * pb = ");
	mul_ab->print(mul_ab);
	kmul_a = kMulPolynomial(pa,params_b[0]);
	printf("pa * 8x = ");
	kmul_a->print(kmul_a);
	DestroyPolynomial(pa);
	DestroyPolynomial(pb);
	DestroyPolynomial(sum_ab);
	DestroyPolynomial(mul_ab);
	DestroyPolynomial(kmul_a);
	return 0;
}