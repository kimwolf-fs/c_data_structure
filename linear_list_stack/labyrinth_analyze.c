#include <stdio.h>
#include <malloc.h>
#include "LinearListStack.h"

int labyrinth[10][10]={
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,1,0,0,0,1,0,1},
	{1,0,0,0,0,1,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,1,1,0,1,1,0,1},
	{1,1,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
};
	
void copyArray(int a[][10],int b[][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			a[i][j] = b[i][j];
		}
	}
}

void printLabyrinth(int labyrinth[][10]){
	int i,j;
	printf("The labyrinth is:\n\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if((i == 1 && j == 1)||(i == 8 && j == 8)){
				printf("**");
			}else{
				if(labyrinth[i][j] == 1){ 
					printf("%c%c",0xa8, 0x80);
				}else if(labyrinth[i][j] == 0){
					printf("  ");
				}else if(labyrinth[i][j] == 2){
					printf("oo");
				}else if(labyrinth[i][j] == 3){
					printf("xx");
				}
			}
		}
		printf("\n");
	}
}

void labyrinthPath(int labyrinth[][10]){
	int labyrinthpath[10][10]; //轨迹图
	int current_step = 0; //当前步数
	int start_i = 1,start_j = 1; //开始位置
	int end_i = 8,end_j = 8; //结束位置
	int current_i = start_i,current_j = start_j; //当前位置
	int current_direction = 0; //0:向下、1：向右、2：向上、3：向左  逆时针旋转方向，数值小的优先级高
	char stack_temp;
	char stack_history_i,stack_history_j;
	LinearListStack *stack_i = InitLinearListStack();
	LinearListStack *stack_j = InitLinearListStack();
	copyArray(labyrinthpath,labyrinth);
	do{
		if(labyrinthpath[current_i][current_j] == 0){ //未走过,且可以走
			labyrinthpath[current_i][current_j] = 2; //留下足迹
			stack_temp = (char)(current_i+0x30);
			stack_i->push(stack_i,&stack_temp);
			stack_temp = (char)(current_j+0x30);
			stack_j->push(stack_j,&stack_temp);//加入路径
			current_step ++;
			printLabyrinth(labyrinthpath);
			if(current_i == end_i && current_j == end_j) break;//到达终点
		}else{
			if(stack_i->length(stack_i)){
				switch(current_direction){
					case 0: 
						if(labyrinthpath[current_i + 1][current_j] == 0){
							stack_i->getTop(stack_i,&stack_history_i);
							stack_j->getTop(stack_j,&stack_history_j);
							if((stack_history_i != current_i+0x30)||(stack_history_j != current_j+0x30)){
								stack_temp = (char)(current_i+0x30);
								stack_i->push(stack_i,&stack_temp);
								stack_temp = (char)(current_j+0x30);
								stack_j->push(stack_j,&stack_temp);//将移出的重新加入路径
							}
							current_i++;//向下找
							current_direction = 0;
						}else{
							current_direction = 1;
						}
						break;
					case 1:
						if(labyrinthpath[current_i][current_j + 1] == 0){
							stack_i->getTop(stack_i,&stack_history_i);
							stack_j->getTop(stack_j,&stack_history_j);
							if((stack_history_i != current_i+0x30)||(stack_history_j != current_j+0x30)){
								stack_temp = (char)(current_i+0x30);
								stack_i->push(stack_i,&stack_temp);
								stack_temp = (char)(current_j+0x30);
								stack_j->push(stack_j,&stack_temp);//将移出的重新加入路径
							}
							current_j++; //向右找
							current_direction = 0;
						}else{
							current_direction = 2;
						}
						break;
					case 2:
						if(labyrinthpath[current_i - 1][current_j] == 0){
							stack_i->getTop(stack_i,&stack_history_i);
							stack_j->getTop(stack_j,&stack_history_j);
							if((stack_history_i != current_i+0x30)||(stack_history_j != current_j+0x30)){
								stack_temp = (char)(current_i+0x30);
								stack_i->push(stack_i,&stack_temp);
								stack_temp = (char)(current_j+0x30);
								stack_j->push(stack_j,&stack_temp);//将移出的重新加入路径
							}
							current_i--;//向上找
							current_direction = 0;
						}else{
							current_direction = 3;
						}
						break;
					case 3:
						if(labyrinthpath[current_i][current_j - 1] == 0){
							stack_i->getTop(stack_i,&stack_history_i);
							stack_j->getTop(stack_j,&stack_history_j);
							if((stack_history_i != current_i+0x30)||(stack_history_j != current_j+0x30)){
								stack_temp = (char)(current_i+0x30);
								stack_i->push(stack_i,&stack_temp);
								stack_temp = (char)(current_j+0x30);
								stack_j->push(stack_j,&stack_temp);//将移出的重新加入路径
							}
							current_j--;//向左找
							current_direction = 0;
						}else{
							current_direction = 4;
						}
						break;
					case 4://四周均不通
						if(labyrinthpath[current_i][current_j] != 1){
							labyrinthpath[current_i][current_j] = 3; //死路标记
							printLabyrinth(labyrinthpath);
						}
						stack_i->pop(stack_i,&stack_temp);
						current_i = (int)stack_temp-0x30;
						stack_j->pop(stack_j,&stack_temp);
						current_j = (int)stack_temp-0x30;
						current_direction = 0;
						break;
				}
			}
		}
	}while(stack_i->length(stack_i));
	if(stack_i->length(stack_i)){
		printf("Maze path:\n");
		printf("i:");
		stack_i->risePrint(stack_i);
		printf("j:");
		stack_j->risePrint(stack_j);
	}else{
		printf("No path found!\n");
	}
	DestroyLinearListStack(stack_i);
	DestroyLinearListStack(stack_j);
}

int main(void)
{
	labyrinthPath(labyrinth);
	return 0;
}