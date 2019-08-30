#include <stdio.h>
#include <malloc.h>
#include "Matrix.h"

int main(void){
	Matrix *m = NULL;
	Matrix *m2 = NULL;
	Matrix *m3 = NULL;
	int rank = 0;
	double norm = 0;
	int a[]={0,0,3,3};
	int b[]={0,0,4,1};
	
	double data[] = {1,1,1,1,2,10,1,10,100};
	double data2[] = {3,2,-1,5};
	double elem;
	Dshape dshape;
	initDshape(&dshape,a);
	
	m = creatMatrixFromDatas(data,9,dshape);
	printarray(m);
	printf("\n");

	m2 = getSymmetricMatrixEigen(m);
	printarray(m2);
	printf("\n");
	
	destroyMatrix(m);
	destroyMatrix(m2);
	destroyMatrix(m3);
	return 0;
}
