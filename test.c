#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

FILE *file_open(void){
	FILE *fp;
	char file_name[20];


	do{
		printf("ファイル名を入力してください：");
		scanf("%s", file_name);
		fp = fopen("sample2.csv", "r");
		if(fp == NULL){
			printf("Errer!ファイルを開けませんでした。\n");
			printf("もう一度、");
		}
	}while (fp == NULL);
	return fp;
}

int main(void){
	int i;
    srand((unsigned)time(NULL));
    for(i=0;i<100;i++){  printf("%d\n",rand()%6+1);  }

}