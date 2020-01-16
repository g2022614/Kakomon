#include <stdio.h>
#include <stdlib.h>

#define NUM 8

struct harea { /* データを格納する構造体　*/
	int flag; /* データ格納の状態 0:無 1:有　*/
	int data;/* データ　*/
};

void hash_add(struct harea a[], int hsize, int key);
int hash_search(struct harea a[], int hsize, int key);

int main(void){
	int i, ky, idx;
	int x[NUM];
	int hsize = 1.5*8;
	struct harea ha[12];/* データ格納場所 */

	for (i = 0; i < hsize; i++)
		ha[i].flag = ha[i].data = 0;
	printf(" Input integer number %d times \n", NUM);
	
	for (i = 0; i < NUM; i++) {
		printf("x[%d]:", i);
		scanf_s("%d", &x[i]);
	}

	for (i = 0; i < NUM; i++) 
		hash_add(ha, hsize, x[i]);
	
	printf("Number to search:");
	scanf_s("%d", &ky);
	idx = hash_search(ha, hsize, ky);
	
	if (idx == -1)
		printf("Searching was failed!\n");
	else
		printf("%d is located at %d \n", ky, idx);

	for (i = 0;i<NUM;i++)
		printf("%d.%d\n",i,ha[i].data);
	return 0;
}

void hash_add(struct harea a[], int hsize, int key){
	int pos;
	pos = key % hsize; /* ハッシュ関数　*/
	while (a[pos].flag != 0) {
		if (a[pos].flag>0) {
			if (a[pos].data == key)
				return;
		}
		pos = (pos + 1) % hsize;/* オープンアドレス　*/
	}
	a[pos].flag = 1; /* データ格納の状態　*/
	a[pos].data = key; /* データ格納　*/
}

int hash_search(struct harea a[], int hsize, int key){
	int pos, ret;
	pos = key % hsize; /* ハッシュ関数　*/
	ret = -1; /* 探索結果　初期値　*/
	while (a[pos].flag != 0) {
		if (a[pos].flag>0) {
			if (a[pos].data == key) {
				ret = pos;
				break;
			}
		}
		pos = (pos + 1) % hsize; /* オープンアドレス　線形探索　*/
	}
	return ret; /* 探索結果　 -1: 失敗　*/
}