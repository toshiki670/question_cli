// main.c on Dec 1st, 2016
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define F_NAME "sample2.cv"
#define ALL    60  /*全問題数*/
#define NUM    32  /*問題番号(何故か26以下だと動かない)*/
#define S_NAME 16  /*略称(10以上)*/
#define L_NAME 64  /*名称(英語)(63以上)*/
#define DES_JP 128 /*説明(日本語)*/


typedef struct{
	char short_name[S_NAME];     /*略称*/
	char long_name[L_NAME];      /*名称(英語)*/
	char description_JP[DES_JP]; /*説明(日本語)*/
}word;
typedef struct{
	char number[NUM];   /*問題番号(現在未使用)*/
	int used_cnt; /*使用回数*/
	word word;    /*word型構造体*/
}ques_data;


FILE *open_file(void);
FILE *open_file_by_self(void);
void make_data(FILE *fp, ques_data *data);


FILE *open_file(void){
	FILE *fp;

	if((fp = fopen(F_NAME, "r")) == NULL){
		printf("Errer!ファイルを開けませんでした。\nプログラムを終了します。\n");
		fclose(fp);
		exit(1);
	}
	return fp;
}


FILE *open_file_by_self(void){
	FILE *fp;
	char file_name[20];

	do{
		printf("ファイル名を入力してください：");
		scanf("%s", file_name);
		fp = fopen("sample2.csv", "r");
		if(fp == NULL){
			printf("Errer!ファイルを開けませんでした。\nもう一度、");
		}
	}while (fp == NULL);
	return fp;
}


void make_data(FILE *fp, ques_data *data){/*構造体にCSVの情報を入れる*/
	int  cnt = 0;
	char number[NUM];
	char short_name[S_NAME];
	char long_name[L_NAME];
	char description_JP[DES_JP];

	while(fscanf(fp, "%[^,], %[^,], %[^,], %s", number, short_name, long_name, description_JP) != EOF){
		if (cnt++ >= ALL) break;
		strcpy(data->number, number);
		data->used_cnt = 0;
		strcpy(data->word.short_name, short_name);
		strcpy(data->word.long_name, long_name);
		strcpy(data->word.description_JP, description_JP);
		data += 1;
	}
	fclose(fp);
}


int main(void){
	ques_data questions[ALL];
	int i = 0;
	
	make_data(open_file(), questions);
	for(i = 0; i < ALL; i += 1){
		srand((unsigned)time(NULL));
		int random = rand() % ALL;
		while(questions[random].used_cnt != 0){
			if(random < ALL - 1){
				random += 1;
			}else{
				random  = 0;
			}
		}
		printf("第%2d門 「%s」の意味は何？(Enterで答えを見る)", i + 1, questions[random].word.short_name);
		getchar();
		printf("正解は「%s」でした。\n", questions[random].word.long_name);
		printf("意味は「%s」です。\n\n", questions[random].word.description_JP);
		questions[random].used_cnt += 1;
	}
	return 0;
}