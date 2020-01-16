#include <stdio.h>
#include <stdlib.h>
#define NUM 1000
#pragma warning(disable:4996)

int lin_search(int x[], int n, int key); /* �֐��v���g�^�C�v */
int lin_search_s(int x[], int n, int key);
int count1 = 0, count2 = 0; /* count1: ����1, count2:����2 */
int main(void) {
	int i = 0, key, idx;
	int x[NUM + 1]; /* �ԕ��@�΍� */
	FILE *fp;
	char fname[64];

	printf("Input file name:");
	scanf("%s", fname);

	fopen_s(&fp, fname, "r");
	if (fp == NULL) {
		printf("%s�t�@�C�����J���܂���\n", fname);
		return -1;
	}
	for (i = 0; i < NUM; i++) {
		fscanf(fp, "%d", &x[i]);
	}
	printf("Number to search:"); /* �T�����l���� */
	scanf_s("%d", &key);

	idx = lin_search(x, NUM, key); /* ���`�T�� */
	if (idx == -1) printf("Searching was failed!\n");
	else printf("%d is located at %d \n", key, idx);

	idx = lin_search(x, NUM, key); /* �ԕ��@ */
	if (idx == -1) printf("Searching was failed!\n");
	else printf("%d is located at %d \n", key, idx);

	printf("���s�񐔁F%d \n", count1);

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

/*�ԕ�*/
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