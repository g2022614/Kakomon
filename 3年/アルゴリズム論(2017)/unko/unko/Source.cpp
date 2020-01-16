#include <stdio.h>
#include <stdlib.h>
#define NUM 1000
#pragma warning(disable:4996)

int lin_search(int x[], int n, int key); /* 関数プロトタイプ */
int lin_search_s(int x[], int n, int key);
int count1 = 0, count2 = 0; /* count1: 条件1, count2:条件2 */
int main(void) {
	int i = 0, key, idx;
	int x[NUM + 1]; /* 番兵法対策 */
	FILE *fp;
	char fname[64];

	printf("Input file name:");
	scanf("%s", fname);

	fopen_s(&fp, fname, "r");
	if (fp == NULL) {
		printf("%sファイルが開けません\n", fname);
		return -1;
	}
	for (i = 0; i < NUM; i++) {
		fscanf(fp, "%d", &x[i]);
	}
	printf("Number to search:"); /* 探索数値入力 */
	scanf_s("%d", &key);

	idx = lin_search(x, NUM, key); /* 線形探索 */
	if (idx == -1) printf("Searching was failed!\n");
	else printf("%d is located at %d \n", key, idx);

	idx = lin_search(x, NUM, key); /* 番兵法 */
	if (idx == -1) printf("Searching was failed!\n");
	else printf("%d is located at %d \n", key, idx);

	printf("試行回数：%d \n", count1);

	fclose(fp);
	return(0);
}

int lin_search(int x[], int n, int key) {
	int i = 0;
	while (1) {
		if (i == n) { count1++; return(-1); }
		else count1++;
		if (x[i] == key) { count2++; return (i); }
		else count2++;
		i++;
	}
}

/*番兵*/
int lin_search_s(int x[], int n, int key) {
	int i = 0;
	x[n] = key; /* sentinel */
	while (1) {
		if (x[i] == key) { count2++; break; }
		else count2++;
		i++;
	}
	if (i == n) { count1++; return(-1); }
	else count1++; return (i);
}