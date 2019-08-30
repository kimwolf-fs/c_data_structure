/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BIGINT_H
#define __BIGINT_H

typedef struct BigInt{
	unsigned int elem_num;  //elem的个数
	char *elem;  //指向大数存放位置，序号0为低位,每个元素保存1位十进制长度数据。
	struct BigInt *higher;  //higher指向更高位，higher = NULL为大数的head
	struct BigInt *lower;   //lower指向更低位，lower = NULL为大数的tear
    char sign; //符号位，1表示正数，-1表示负数，只有head node使用此符号位。
}BigInt;



#endif