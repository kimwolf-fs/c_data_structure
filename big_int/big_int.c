#include <stdio.h>
#include <malloc.h>
#include "BigInt.h"

unsigned int StrLen(char *num){
	unsigned int i = 0;
	while(*(num + i) != '\0'){
		i++;
	}
	return i;
}

BigInt *BigIntInit(char *num, unsigned int str_len){
	
	BigInt *big_int = NULL;
	unsigned int num_len; //大数的十进制位数
	unsigned int num_index = 0; //十进制数的游标

	if((!num) || (str_len == 0)) return NULL;
	if(str_len > StrLen(num)){
		printf("str lenth not match!\n");
		return NULL;
	} 
	big_int = (BigInt *)malloc(sizeof(BigInt));
 	if(!big_int) return NULL; 

	big_int->higher = NULL;
	big_int->lower = NULL;

	if(*num == '-'){
		num_len = str_len - 1;
		big_int->sign = -1;
		num_index = 1;
	}else if(*num == '+'){
		num_len = str_len - 1;
		big_int->sign = 1;
		num_index = 1;
	}else if((*num >= '0') && (*num <= '9')){
		num_len = str_len;
		big_int->sign = 1;
		num_index = 0;
	}else{
		printf("error format!\n");
		free(big_int);
		return NULL;
	}

	big_int->elem_num = num_len;
	big_int->elem = (char *)malloc(big_elem_len*sizeof(char));
	if(!big_int->elem){
		free(big_int);
		return NULL;
	}
	for (int i = 0; i < num_len; i++){
		if((*(num + i) >= '0') && (*(num + i) <= '9')){
			*(big_int->elem + i) = *(num + i) - '0';
		}else{
			free(big_int->elem);
			free(big_int);
			big_int = NULL;
			printf("error format!\n");
			break;
		}
	}
	return big_int;
}

BigInt *BigIntFindHead(BigInt *big_int_node){
	BigInt *big_node_index = big_int_node;
	while(big_node_index->higher){
		big_node_index = big_node_index->higher;
	}
	return big_node_index;
}

BigInt *BigIntFindTear(BigInt *big_int_node){
	BigInt *big_node_index = big_int_node;
	while(big_node_index->lower){
		big_node_index = big_node_index->lower;
	}
	return big_node_index;	
}

void BigIntPrintNode(BigInt *big_int_node){
	if(!big_int_node) return;
	if(!big_int_node->elem) return;
	for(int i = 0; i < big_int_node->elem_num; i++){
		printf("%d", *(big_int_node->elem + i));	
	}
}

void BigIntPrint(BigInt *big_int){
	BigInt *big_node_index = big_int;
	unsigned int zero_head_index = 0;
	if(!big_int) return;
	if(!big_int->elem) return;
	if(big_int->sign == -1){
		printf("-");
	}
	while(*(big_node_index + zero_head_index) == 0){
		zero_head_index ++;
		if(zero_head_index == big_node_index->elem_num){
			big_node_index = big_node_index->lower;
			zero_head_index = 0;
			if(!big_node_index){
				printf("0");
				break;
			} 
		}
	}
	if((big_node_index) && (zero_head_index != 0)){
		while(zero_head_index < big_node_index->elem_num){
			printf("%d", *(big_node_index->elem + zero_head_index));	
			zero_head_index ++;
		}
		big_node_index = big_node_index->lower;
	}
	while(big_node_index){
		BigIntPrintNode(big_node_index);
		big_node_index = big_node_index->lower;
	}
	printf("\n");
}

unsigned long long BigIntGetLen(BigInt *big_int){
	BigInt *big_node_index;
	unsigned long long big_int_len;
	if(!big_int) return 0;
	big_int_len = big_int->elem_num;
	while(big_node_index->lower){
		big_int_len += big_node_index->lower->elem_num;
		big_node_index = big_node_index->lower;
	}
	return big_int_len;
}

//big_hi + big_lo -> big_hi
void BigIntCat(BigInt *big_hi, BigInt *big_lo){
	BigInt *big_hi_tear;
	if(!big_hi) return NULL;
	if(!big_hi->elem) return NULL;
	big_hi_tear = BigIntFindTear(big_hi);
	big_hi_tear->lower = big_lo;
}

int _BigIntCmpWithSameLen(BigInt *big_a, BigInt *big_b, unsigned long long big_len){
	unsigned long long big_a_acc = 0;
	unsigned long long big_b_acc = 0;
	int result = 0;
	BigInt *big_a_index = big_a;
	BigInt *big_b_index = big_b;
	for (unsigned long long i = 0; i < big_len; ++i)
	{
		unsigned int j = i - big_a_acc;
		unsigned int k = i - big_b_acc;
		if(j >= big_a_index->elem_num){
			big_a_acc += big_a_index->elem_num;
			big_a_index = big_a_index->lower;
			j = 0;
		}
		if(k >= big_b_index->elem_num){
			big_b_acc += big_b_index->elem_num;
			big_b_index = big_b_index->lower;	
			k = 0;		
		}

		if(*(big_a_index->elem + j) > *(big_b_index->elem + k)){
			result = 1;
			break;
		}else if(*(big_a_index->elem + j) < *(big_b_index->elem + k)){
			result = -1;
			break;	
		}
	}
	return result;
}

int BigIntUnsignedCmp(BigInt *big_a, BigInt *big_b){
	unsigned long long big_a_len;
	unsigned long long big_b_len;
	int result;
	big_a_len = BigIntGetLen(big_a);
	big_b_len = BigIntGetLen(big_b);
	if(big_a_len > big_b_len){
		return 1;
	}else if(big_a_len < big_b_len){
		return -1;
	}else{
		if(big_a_len == 0){
			return 0;
		}else{
			result = _BigIntCmpWithSameLen(big_a, big_b, big_a_len);
		}
	}
	return result; 
}

int BigIntCmp(BigInt *big_a, BigInt *big_b){
	int result;
	if((big_a) && (!big_b)) return 1;
	if((!big_a) && (big_b)) return -1;
	if((!big_a) && (!big_b)) return 0;

	if(big_a->sign == big_b->sign){
		result = BigIntUnsignedCmp(big_a, big_b);
		if(big_a->sign == -1){
			result = -result;
		}
	}else{
		if(big_a->sign == 1){
			result = 1;
		}else{
			result = -1;
		}
	}
	return result; 
}

BigInt *BigIntCopy(BigInt *big_int){
	BigInt *result;
	BigInt *result_node1;
	BigInt *result_node2;
	BigInt *big_int_node = big_int;
	if(!big_int) return NULL;
	result = (BigInt *)malloc(sizeof(BigInt));
	if(!result){ 
		return NULL;
	} 
	result->higher = NULL;
	result->sign = big_int->sign;
	result_node1 = result;
	while(big_int_node){
		result_node1->elem_num = big_int_node->elem_num;
		result_node1->elem = (char *)malloc(result_node1->elem_num * sizeof(char));
		if(!result_node1->elem){
			result_node1 = BigIntFindHead(result_node1);
			BigIntDestroy(result_node1);
			result = NULL;
			break;
		}
		for (unsigned int i = 0; i < result_node1->elem_num; i++){
			*(result_node1->elem + i) = *(big_int_node->elem + i);
		}
		big_int_node = big_int_node->lower;
		result_node2 = (BigInt *)malloc(sizeof(BigInt));
		if(!result_node2){
			result_node1 = BigIntFindHead(result_node1);
			BigIntDestroy(result_node1);
			result = NULL;
			break;			
		}
		result_node1->lower = result_node2;
		result_node2->higher = result_node1;
		result_node1 = result_node2;
	}
	result_node1->lower = NULL;
	return result;
}

BigInt *BigIntSplitNode(BigInt *big_int, unsigned int split_index){
	BigInt *big_new_node;
	if(!big_int) return NULL;
	if(big_int->elem_num <= split_index) return NULL;
	if(split_index == 0){
		big_new_node = big_int;
		big_int = NULL;
		return big_new_node;
	}
	big_new_node = (BigInt *)malloc(sizeof(BigInt));
	if(!big_new_node) return NULL;
	big_new_node->elem_num = big_int->elem_num - split_index;
	big_new_node->num = (char *)malloc(big_new_node->elem_num * sizeof(char));
	if(!big_new_node->num){
		free(big_new_node);
		return NULL;
	}
	for (unsigned int i = split_index; i < big_int->elem_num ; ++i){
		*(big_new_node->num + i - split_index) = *(big_int->num + i);
	}
	big_new_node->lower = big_int->lower;
	big_new_node->higher = NULL;
	big_int->elem_num = split_index;
	big_int->num = realloc(big_int->num, split_index);
	big_int->lower = NULL;
	return big_new_node;
}

BigInt *BigIntSplit(BigInt *big_int, unsigned long long split_index){
	BigInt *big_new_node;
	BigInt *big_node_index;
	unsigned long long big_int_len;
	unsigned int node_split_index;
	if(!big_int) return NULL;
	big_int_len = BigIntGetLen(big_int);
	if(big_int_len <= split_index) return NULL;
	if(split_index == 0){
		big_new_node = big_int;
		big_int = NULL;
		return big_new_node;		
	}
	big_int_len = big_int->elem_num;
	big_node_index = big_int;
	while(split_index >= big_int_len){
		big_int_len += big_new_node->elem_num;
		big_node_index = big_new_node->lower;
	}
	node_split_index = big_int_len - split_index;
	node_split_index = big_node_index->elem_num - node_split_index;
	big_new_node = BigIntSplitNode(big_node_index, node_split_index);
	return big_new_node;
}

void BigIntDestroy(BigInt *big_int){
	BigInt *big_int_node;
	BigInt *big_int_index;
	if(!big_int) return;
	big_int_node = BigIntFindHead(big_int);
	while(big_int_node){
		if(big_int_node->elem){
			free(big_int_node->elem);
		}
		big_int_index = big_int_node->lower;
        free(big_int_node);
        big_int_node = big_int_index;
	}
}

BigInt *BigIntUnsignedAdd(BigInt *big_a, BigInt *big_b, unsigned char lo_carry){
	BigInt *result;
	BigInt *result_append;
	BigInt *big_a_node;
	BigInt *big_b_node;

	unsigned long long big_a_len;
	unsigned long long big_b_len;	
	unsigned long long result_len;	

	unsigned int result_index;
	unsigned int big_a_elem_index;
	unsigned int big_b_elem_index;

	unsigned char carry = lo_carry;
	char temp = 0;

	if((!big_a) || (!big_b)) return NULL;

	result = (BigInt *)malloc(sizeof(BigInt));
	if(!result){ 
		return NULL;
	} 

	result->lower = NULL;

	big_a_node = BigIntFindTear(big_a);
	big_b_node = BigIntFindTear(big_b);
	big_a_len = BigIntGetLen(big_a);
	big_b_len = BigIntGetLen(big_b);

	if(big_a_len > big_b_len){
		result_len = big_a_len;
	}else{
		result_len = big_b_len;
	}

	if(result_len > 0xFFFFFFFF){
		result->elem_num = 0xFFFFFFFF;
		result->elem = (char *)malloc(result->elem_num * sizeof(char));
		result_len -= 0xFFFFFFFF;
	}else{
		result->elem_num = result_len;
		result->elem = (char *)malloc(result->elem_num * sizeof(char));
	}
	if(!result->elem){
		free(result);
		return NULL;
	}

	result_index = result->elem_num;
	big_a_elem_index = big_a_node->elem_num;
	big_b_elem_index = big_b_node->elem_num;

	while((big_a_node != NULL) && (big_b_node != NULL)){
		big_a_elem_index--;
		big_b_elem_index--;
		result_index--;

		temp = *(big_a_node + big_a_elem_index) + *(big_b_node + big_b_elem_index) + carry;
		if(temp > 10){
			*(result->elem + result_index) = temp - 10;
			carry = 1;
		}else{
			*(result->elem + result_index) = temp;
			carry = 0;
		} 

		if(result_index == 0){
			result_append = (BigInt *)malloc(sizeof(BigInt));
			if(!result_append){
				BigIntDestroy(result);
				return NULL;
			}
			if(result_len > 0xFFFFFFFF){
				result_append->elem_num = 0xFFFFFFFF;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
				result_len -= 0xFFFFFFFF;
			}else{
				result_append->elem_num = result_len;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
			}
			if(!result->elem){
				BigIntDestroy(result);
				free(result_append);
				return NULL;
			}
			result_index = result_append->elem_num;
			result->higher = result_append;
			result_append->lower = result;
			result = result_append;
		}

		if(big_a_elem_index == 0){
			big_a_node = big_a_node->higher;
			if(big_a_node){
				big_a_elem_index = big_a_node->elem_num;
			}
			
		}
		if(big_b_elem_index == 0){
			big_b_node = big_b_node->higher;
			if(big_b_node){
				big_b_elem_index = big_b_node->elem_num;	
			} 	
		}
	}

	while(big_a_node != NULL){
		big_a_elem_index--;
		result_index--;
		temp = *(big_a_node + big_a_elem_index) + carry;
		if(temp > 10){
			*(result->elem + result_index) = temp - 10;
			carry = 1;
		}else{
			*(result->elem + result_index) = temp;
			carry = 0;
		} 		

		if(result_index == 0){
			result_append = (BigInt *)malloc(sizeof(BigInt));
			if(!result_append){
				BigIntDestroy(result);
				return NULL;
			}
			if(result_len > 0xFFFFFFFF){
				result_append->elem_num = 0xFFFFFFFF;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
				result_len -= 0xFFFFFFFF;
			}else{
				result_append->elem_num = result_len;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
			}
			if(!result->elem){
				BigIntDestroy(result);
				free(result_append);
				return NULL;
			}
			result_index = result_append->elem_num;
			result->higher = result_append;
			result_append->lower = result;
			result = result_append;
		}

		if(big_a_elem_index == 0){
			big_a_node = big_a_node->higher;
			if(big_a_node){
				big_a_elem_index = big_a_node->elem_num;
			}
		}			
	}

	while(big_b_node != NULL){
		big_b_elem_index--;
		result_index--;
		temp = *(big_b_node + big_b_elem_index) + carry;
		if(temp > 10){
			*(result->elem + result_index) = temp - 10;
			carry = 1;
		}else{
			*(result->elem + result_index) = temp;
			carry = 0;
		} 	

		if(result_index == 0){
			result_append = (BigInt *)malloc(sizeof(BigInt));
			if(!result_append){
				BigIntDestroy(result);
				return NULL;
			}
			if(result_len > 0xFFFFFFFF){
				result_append->elem_num = 0xFFFFFFFF;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
				result_len -= 0xFFFFFFFF;
			}else{
				result_append->elem_num = result_len;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
			}
			if(!result->elem){
				BigIntDestroy(result);
				free(result_append);
				return NULL;
			}
			result_index = result_append->elem_num;
			result->higher = result_append;
			result_append->lower = result;
			result = result_append;
		}	

		if(big_b_elem_index == 0){
			big_b_node = big_b_node->higher;
			if(big_b_node){
				big_b_elem_index = big_b_node->elem_num;	
			}		
		}	

	}

	if(carry == 1){
		result_append = (BigInt *)malloc(sizeof(BigInt));
		if(!result_append){
			BigIntDestroy(result);
			return NULL;
		}
		result_append->elem_num = 1;
		result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
		if(!result_append->elem){
			BigIntDestroy(result);
			free(result_append);
			return NULL;			
		}
		*(result_append->elem) = 1;
		result_append->higher =	NULL;
		result_append->lower = result;
		result->higher = result_append;
		return result_append;
	}else{
		result->higher = NULL;
		return result;
	}
}

//big_a - big_b
//assume big_a > big_b
BigInt *BigIntUnsignedSub(BigInt *big_a, BigInt *big_b, unsigned char lo_carry){
	BigInt *result;
	BigInt *result_append;
	BigInt *big_a_node;
	BigInt *big_b_node;

	unsigned long long big_a_len;
	unsigned long long big_b_len;	
	unsigned long long result_len;	

	unsigned int result_index;
	unsigned int big_a_elem_index;
	unsigned int big_b_elem_index;

	unsigned char carry = lo_carry;
	char temp = 0;

	if((!big_a) || (!big_b)) return NULL;

	result = (BigInt *)malloc(sizeof(BigInt));
	if(!result){ 
		return NULL;
	} 

	result->lower = NULL;

	big_a_node = BigIntFindTear(big_a);
	big_b_node = BigIntFindTear(big_b);
	big_a_len = BigIntGetLen(big_a);
	big_b_len = BigIntGetLen(big_b);
	result_len = big_a_len;

	if(result_len > 0xFFFFFFFF){
		result->elem_num = 0xFFFFFFFF;
		result->elem = (char *)malloc(result->elem_num * sizeof(char));
		result_len -= 0xFFFFFFFF;
	}else{
		result->elem_num = result_len;
		result->elem = (char *)malloc(result->elem_num * sizeof(char));
	}
	if(!result->elem){
		free(result);
		return NULL;
	}

	result_index = result->elem_num;
	big_a_elem_index = big_a_node->elem_num;
	big_b_elem_index = big_b_node->elem_num;

	while((big_a_node != NULL) && (big_b_node != NULL)){
		big_a_elem_index--;
		big_b_elem_index--;
		result_index--;

		temp = *(big_a_node + big_a_elem_index) - carry;

		if(temp < *(big_b_node + big_b_elem_index)){
			temp += 10 - *(big_b_node + big_b_elem_index);
			carry = 1;
		}else{
			temp -= *(big_b_node + big_b_elem_index);
			carry = 0;
		}
		*(result->elem + result_index) = temp;

		if(result_index == 0){
			result_append = (BigInt *)malloc(sizeof(BigInt));
			if(!result_append){
				BigIntDestroy(result);
				return NULL;
			}
			if(result_len > 0xFFFFFFFF){
				result_append->elem_num = 0xFFFFFFFF;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
				result_len -= 0xFFFFFFFF;
			}else{
				result_append->elem_num = result_len;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
			}
			if(!result->elem){
				BigIntDestroy(result);
				free(result_append);
				return NULL;
			}
			result_index = result_append->elem_num;
			result->higher = result_append;
			result_append->lower = result;
			result = result_append;
		}

		if(big_a_elem_index == 0){
			big_a_node = big_a_node->higher;
			if(big_a_node){
				big_a_elem_index = big_a_node->elem_num;
			}
			
		}
		if(big_b_elem_index == 0){
			big_b_node = big_b_node->higher;
			if(big_b_node){
				big_b_elem_index = big_b_node->elem_num;	
			} 	
		}
	}

	while(big_a_node != NULL){
		big_a_elem_index--;
		result_index--;
		temp = *(big_a_node + big_a_elem_index) - carry;
		if(temp < 0){
			*(result->elem + result_index) = temp + 10;
			carry = 1;
		}else{
			*(result->elem + result_index) = temp;
			carry = 0;
		} 		

		if(result_index == 0){
			result_append = (BigInt *)malloc(sizeof(BigInt));
			if(!result_append){
				BigIntDestroy(result);
				return NULL;
			}
			if(result_len > 0xFFFFFFFF){
				result_append->elem_num = 0xFFFFFFFF;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
				result_len -= 0xFFFFFFFF;
			}else{
				result_append->elem_num = result_len;
				result_append->elem = (char *)malloc(result_append->elem_num * sizeof(char));
			}
			if(!result->elem){
				BigIntDestroy(result);
				free(result_append);
				return NULL;
			}
			result_index = result_append->elem_num;
			result->higher = result_append;
			result_append->lower = result;
			result = result_append;
		}

		if(big_a_elem_index == 0){
			big_a_node = big_a_node->higher;
			if(big_a_node){
				big_a_elem_index = big_a_node->elem_num;
			}
		}			
	}
	result->higher = NULL;
	return result;
}

BigInt *BigIntAdd(BigInt *big_a, BigInt *big_b){
	BigInt *result;

	if((big_a) && (!big_b)){
		result = BigIntCopy(big_a);
		return result;
	} 
	if((!big_a) && (big_b)){
		result = BigIntCopy(big_b);
		return result;		
	} 
	if((!big_a) && (!big_b)) return NULL;

	if(big_a->sign == big_b->sign){
		result = BigIntUnsignedAdd(big_a, big_b, 0);
		if(!result) return NULL;
		if(big_a->sign == -1){
			result->sign = -1;
		}else{
			result->sign = 1;
		}
	}else{
		if(big_a->sign == 1){
			if(BigIntUnsignedCmp(big_a, big_b) >= 0){
				result = BigIntUnsignedSub(big_a, big_b, 0);
				if(!result) return NULL;
				result->sign = 1;
			}else{
				result = BigIntUnsignedSub(big_b, big_a, 0);
				if(!result) return NULL;
				result->sign = -1;				
			}
		}else{
			if(BigIntUnsignedCmp(big_a, big_b) > 0){
				result = BigIntUnsignedSub(big_a, big_b, 0);
				if(!result) return NULL;
				result->sign = -1;	
			}else{
				result = BigIntUnsignedSub(big_b, big_a, 0);
				if(!result) return NULL;
				result->sign = 1;					
			}		
		}
	}
	return result;
}

BigInt *BigIntSub(BigInt *big_a, BigInt *big_b){
	BigInt *result;

	if((big_a) && (!big_b)){
		result = BigIntCopy(big_a);
		return result;
	} 
	if((!big_a) && (big_b)){
		result = BigIntCopy(big_b);
		return result;
	} 
	if((!big_a) && (!big_b)) return NULL;

	if(big_a->sign == 1){
		if(big_b->sign == 1){
			if(BigIntUnsignedCmp(big_a, big_b) >= 0){
				result = BigIntUnsignedSub(big_a, big_b, 0);
				if(!result) return NULL;
				result->sign = 1;
			}else{
				result = BigIntUnsignedSub(big_b, big_a, 0);
				if(!result) return NULL;
				result->sign = -1;				
			}
		}else{
			result = BigIntUnsignedAdd(big_a, big_b, 0);
			if(!result) return NULL;
			result->sign = 1;
		}
	}else{
		if(big_b->sign == 1){
			result = BigIntUnsignedAdd(big_a, big_b, 0);
			if(!result) return NULL;
			result->sign = -1;			
		}else{
			if(BigIntUnsignedCmp(big_a, big_b) > 0){
				result = BigIntUnsignedSub(big_a, big_b, 0);
				if(!result) return NULL;
				result->sign = -1;
			}else{
				result = BigIntUnsignedSub(big_b, big_a, 0);
				if(!result) return NULL;
				result->sign = 1;				
			}			
		}
	}
	return result;
}

int main(int argc, char *argv[]){
	char *big_int_char;
	BigInt *big_int;

	big_int_char = (char *)malloc(65535 * sizeof(char));
	if(!big_int_char) return 0;

	printf("please input a big num\n");
	scanf("%s", big_int_char);
	big_int = BigIntInit(big_int_char, StrLen(big_int_char));
	BigIntPrint(big_int);

	BigIntDestroy(big_int);
	free(big_int_char);

	return 0;
}





