#include<stdio.h>
#include<stdlib.h>
#define NUM 1000
#pragma warning(disable:4996)
int bin_search(int a[], int n, int key); /*関数プロトタイプ*/
int bubble(int a[], int n);
int count = 0;
int main(void) {
	int i, key, idx;
	int x[NUM + 1]; /* 番兵法対策 */
	FILE *fp;
	char fname[64];
	printf("Input file name:");
	scanf("%s", fname);

	fopen_s(&fp, fname, "r");
	if (fp == NULL) {
		printf("%sファイルを開けません\n", fname);
		return -1;
	}
	for (i = 0; i<NUM; i++) {
		fscanf(fp, "%d", &x[i]);
	}
	bubble(x, NUM); /* bubblesort */

	printf("Number to search:");
	scanf("%d", &key);
	idx = bin_search(x, NUM, key);
	if (idx == -1) printf("Searching was failed!\n");
	else printf("%d is located %d \n", key, idx);
	printf("試行回数%d\n\n", count);
	return 0;
}


int bin_search(int a[], int n, int key) {
	int pl = 0;
	int pr = n - 1;
	int pc;
	do {
		pc = (pl + pr) / 2;
		if (a[pc] == key)
			return(pc);
		else if (a[pc]<key) {
			pl = pc + 1;
			count++;
		}
		else {
			pr = pc - 1;
			count++;
		}
	} while (pl <= pr);
	return -1;
}

int bubble(int x[], int n) {
	int i, j, tmp, count = 0;
	for (i = 0; i<n - 1; i++) {
		for (j = n - 1; j>i; j--) {
			if (x[j - 1]>x[j]) {
				tmp = x[j];
				x[j] = x[j - 1];
				x[j - 1] = tmp;
				count++;
			}
		}
	}
	return count;
}