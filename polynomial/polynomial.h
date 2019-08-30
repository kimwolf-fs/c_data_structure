/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POLYNOMIAL_H
#define __POLYNOMIAL_H
/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct ElemType{
	double coefficient; //系数
	double exponent;//指数
}ElemType;

typedef struct Node{
	ElemType elem;  //存储空间
	struct Node *next;
}Node;

typedef struct Polynomial{
	Node *This;
	void (*clear)(struct Polynomial *This);
	int (*isEmpty)(struct Polynomial *This);
	int (*length)(struct Polynomial *This);
	void (*print)(struct Polynomial *This);
	int (*appendElem)(struct Polynomial *This, ElemType e);
}Polynomial;

/* Exported macro ------------------------------------------------------------*/
Polynomial *CreatePolynomial(ElemType *params,int length);
void DestroyPolynomial(Polynomial *L);
Polynomial *addPolynomial(Polynomial *pa,Polynomial *pb);
Polynomial *subPolynomial(Polynomial *pa,Polynomial *pb);
Polynomial *kMulPolynomial(Polynomial *pa,ElemType a);
Polynomial *mulPolynomial(Polynomial *pa,Polynomial *pb);

#endif