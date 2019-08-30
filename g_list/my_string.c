#include <stdio.h>
#include <malloc.h>
#include "MyString.h"

MyString *myStringAssign(char *str){
	int i,str_length = 0;
	MyString *S = (MyString *)malloc(sizeof(MyString));
	if(!S) return NULL;
	while(*(str+str_length) != '\0'){
		str_length++;
	}
	str_length++;
	S->str = (char *)malloc(str_length*sizeof(char));
	S->size = str_length;
	if(!S->str){
		free(S);
		return NULL;
	}
	S->length = str_length - 1; 
	for(i=0;i<str_length;i++){
		*(S->str + i) = *(str + i);
	}
	return S;
}

int myStringLength(MyString *S){
	if(S){
		return S->length;
	}else{
		return 0;
	}
}

int myStringRemainSpace(MyString *S){
	if(S){
		return S->size - S->length -1;
	}else{
		return 0;
	}
}

int isMyStringEmpty(MyString *S){
	if(!S) return 0;
	if(S->length){
		return 0;
	}else{
		return 1;
	}
}

int clearMyString(MyString *S){
	if(S){
		if(S->str){
			*S->str = '\0';
		}
		S->length = 0;
	}
}

void destroyMyString(MyString *S){
	if(S){
		if(S->str){
			free(S->str);
		}
		free(S);
		S = NULL;
	}
}

int printMyString(MyString *S){
	if(S){
		if(S->str){
			printf("%s, ",S->str);
		}
		printf("length :%d\n",S->length);
	}
	return 0;
}

int compareMyString(MyString *S1,MyString *S2){
	int i;
	int result = 0;
	if(!S1 || !S2) return result;
	for(i=0;i<S1->length && i<S2->length;i++){
		if(*(S1->str+i) != *(S2->str+i)){
			result = *(S1->str+i) - *(S2->str+i);
			break;
		}
	}
	if(result == 0){
		result = S1->length - S2->length;
	}
	return result;
}

MyString *copyMyString(MyString *S){
	int i;
	if(!S || !S->str) return NULL;
	MyString *temp = (MyString *)malloc(sizeof(MyString));
	if(!temp) return NULL;
	temp->size = S->length + 1;
	temp->str = (char *)malloc(temp->size*sizeof(char));
	if(!temp->str){
		free(temp);
		return NULL;
	}
	temp->length = S->length; 
	for(i=0;i<S->length+1;i++){
		*(temp->str + i) = *(S->str + i);
	}
	return temp;
}

int myStringIndexChar(MyString *S,char indexElem,int pos){
	int index = -1;
	int i;
	if(!S) return -1;
	for(i=pos;i<S->length;i++){
		if(*(S->str + i) == indexElem){
			index = i;
			break;
		}
	}
	return index;
}

int insertMyString(MyString *S1,MyString *S2,int pos){
	int i;
	if(!S1 || !S1->str || !S2 || !S2->str) return -1;
	if(pos < 0 || pos > S1->length) return -1;
	if(myStringRemainSpace(S1) < S2->length){
		S1->size += S2->length - myStringRemainSpace(S1);
		S1->str = (char *)realloc(S1->str,S1->size*sizeof(char));
		if(!S1->str) return -1;
	}
	for(i=S1->length;i>=pos;i--){
		*(S1->str + S2->length + i) = *(S1->str + i);
	}
	for(i=0;i<S2->length;i++){
		*(S1->str + pos + i) = *(S2->str + i);
	}
	S1->length += S2->length;
	return 0;
}

MyString *substrMyString(MyString *S,int start,int end){
	int i,length;
	if(start < 0 || start >= S->length || end <= 0 || end > S->length || end <= start) return NULL;
	MyString *temp = (MyString *)malloc(sizeof(MyString));
	if(!temp) return NULL;
	length = end - start;
	temp->size = length+1;
	temp->str = (char *)malloc(temp->size*sizeof(char));
	if(!temp->str){
		free(temp);
		return NULL;
	}
	for(i=0;i<length;i++){
		*(temp->str + i) = *(S->str + start + i);
	}
	*(temp->str + length) = '\0';
	temp->length = length;
	return temp;
}

int deleteMyString(MyString *S,int start,int end){
	int i,length;
	if(start < 0 || start >= S->length || end <= 0 || end > S->length || end <= start) return -1;
	length = S->length - end + 1;
	for(i=0;i<=length;i++){
		*(S->str + start + i) = *(S->str + end + i);
	}
	S->length -= (end - start);
	return 0;
}

int concatMyString(MyString *S1,MyString *S2){
	int i;
	if(!S2->str || !S1) return -1;
	if(myStringRemainSpace(S1) < S2->length){
		S1->size += (S2->length - myStringRemainSpace(S1));
		S1->str = (char *)realloc(S1->str,S1->size*sizeof(char));
		if(!S1->str) return -1;
	}
	for(i=0;i<=S2->length;i++){
		*(S1->str + S1->length + i) = *(S2->str + i);
	}
	S1->length += S2->length;
	return 0;
}

int replaceMyString(MyString *S1,MyString *S2,int start,int end){
	if(start < 0 || start >= S1->length || end <= 0 || end > S1->length || end < start) return -1;
	if(end>start){
		if(deleteMyString(S1,start,end) == -1){
			return -1;
		}
	}
	if(insertMyString(S1,S2,start) == -1){
		return -1;
	}else{
		return 0;
	}
}

MyStringArray *splitMyString(MyString *S,char splitElem){
	int start = 0,end = 0,index = 0;
	MyStringArray *strarray = NULL;
	MyString *strtemp = NULL;
	index = myStringIndexChar(S,splitElem,0);
	if(index == -1) return NULL;
	strarray = InitMyStringArray();
	end = index;
	if(end != start){
		strtemp = substrMyString(S,start,end);
		strarray->tearPush(strarray,strtemp);
		destroyMyString(strtemp);
		if(end == S->length){
			return strarray;
		}
	}
	index++;
	start = index;
	while(index > 0){
		index = myStringIndexChar(S,splitElem,index);
		if(index != -1){
			end = index;
			strtemp = substrMyString(S,start,end);
			strarray->tearPush(strarray,strtemp);
			destroyMyString(strtemp);
			if(end == S->length){
				break;
			}
			index++;
			start = index;
		}
	}
	if(end != S->length){
		end = S->length;
		strtemp = substrMyString(S,start,end);
		strarray->tearPush(strarray,strtemp);
		destroyMyString(strtemp);
	}
	return strarray;
}

static int *getKMPNext(MyString *substr){
	int *nextval = (int *)malloc((substr->length)*sizeof(int));
	int j=0,k=-1;
	if(nextval){
		*nextval = -1;
		while(j<substr->length){
			if(k == -1 || *(substr->str+j) == *(substr->str+k)){
				if(*(substr->str+(++j)) == *(substr->str+(++k))){ //两个字符相等时跳过
					*(nextval+j) = *(nextval+k);
				}else{
					*(nextval+j) = k;
				}
			}else{
				k = *(nextval+k);
			}
		}
		return nextval;
	}else{
		return NULL;
	}
}

int myStringIndexSubString(MyString *S,MyString *substr,int pos){ //KMP算法
	int i = pos,j = 0;
	if(!S || !substr || pos > S->length) return -1;
	int *nextval = getKMPNext(substr);
	if(!nextval) return -1;
	while(i < S->length && j < substr->length){
		if(*(S->str + i) == *(substr->str + j)){
			i++; 
			j++; 
		}else{
			j = *(nextval+j); //i不需要回溯，j回到指定位置
			if(j == -1){
				i++; //当j为-1时，要移动的是i
				j++; //j归0
			}
		}
	}
	free(nextval);
	if(j == substr->length){
		return i - j;
	}else{
		return -1;
	}
}

static int parenthesesMatching(MyString *S){
	if(!S) return 0; 
	int bracket_count = 0,str_index = 0;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '(') return 0;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '('){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == ')'){
			if(bracket_count){
				bracket_count --;
			}else{
				bracket_contained = 0;
				break;
			}
		}
		str_index++;
	}
	if(bracket_contained){
		if(bracket_count == 0) return 1;
	}
	return 0;
}

static int squareBracketMatching(MyString *S){
	if(!S) return 0; 
	int bracket_count = 0,str_index = 0;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '[') return 0;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '['){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == ']'){
			if(bracket_count){
				bracket_count --;
			}else{
				bracket_contained = 0;
				break;
			}
		}
		str_index++;
	}
	if(bracket_contained){
		if(bracket_count == 0) return 1;
	}
	return 0;
}

static int braceMatching(MyString *S){
	if(!S) return 0; 
	int bracket_count = 0,str_index = 0;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '{') return 0;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '{'){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == '}'){
			if(bracket_count){
				bracket_count --;
			}else{
				bracket_contained = 0;
				break;
			}
		}
		str_index++;
	}
	if(bracket_contained){
		if(bracket_count == 0) return 1;
	}
	return 0;
}

int isBracketMatching(MyString *S,char leftBracketChar){
	int isMatching = 0;
	switch(leftBracketChar){
		case '(': 
			isMatching = parenthesesMatching(S);
			break;
		case '[':
			isMatching = squareBracketMatching(S);
			break;
		case '{':
			isMatching = braceMatching(S);
			break;
	}
	return isMatching;
}

static int getMatchingParenthesisIndex(MyString *S,int leftbracketIndex){
	if(!S) return -1; 
	int bracket_count = 0,str_index = leftbracketIndex;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '(') return -1;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '('){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == ')'){
			bracket_count --;
			if(bracket_count == 0) break;
		}
		str_index++;
	}
	if(str_index > S->length) return -1;
	return str_index;
}

static int getMatchingSquareBracketIndex(MyString *S,int leftbracketIndex){
	if(!S) return -1; 
	int bracket_count = 0,str_index = leftbracketIndex;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '[') return -1;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '['){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == ']'){
			bracket_count --;
			if(bracket_count == 0) break;
		}
		str_index++;
	}
	if(str_index > S->length) return -1;
	return str_index;
}

static int getMatchingBraceIndex(MyString *S,int leftbracketIndex){
	if(!S) return -1; 
	int bracket_count = 0,str_index = leftbracketIndex;
	int bracket_contained = 0;
	if(*(S->str+str_index) != '{') return -1;
	while(*(S->str+str_index) != '\0'){
		if(*(S->str+str_index)  == '{'){
			bracket_contained = 1;
			bracket_count++;
		}else if(*(S->str+str_index) == '}'){
			bracket_count --;
			if(bracket_count == 0) break;
		}
		str_index++;
	}
	if(str_index > S->length) return -1;
	return str_index;
}

int getMatchingBracketIndex(MyString *S,char leftBracketChar,int leftbracketIndex){
	int index = 0;
	switch(leftBracketChar){
		case '(': 
			index = getMatchingParenthesisIndex(S,leftbracketIndex);
			break;
		case '[':
			index = getMatchingSquareBracketIndex(S,leftbracketIndex);
			break;
		case '{':
			index = getMatchingBraceIndex(S,leftbracketIndex);
			break;
	}
	return index;
}