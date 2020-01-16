#include <stdio.h>
#define swap(type,x,y) do {type t=x; x=y; y=t;} while(0)
#define NUM 5

void downheap(int a[], int left, int right); /* 関数プロトタイプ　*/
void heapsort(int a[], int n);
int count0 = 0, count1 = 0,count2 = 0;/* count0:比較,count1:交換,count2:挿入 */

int main(void){

	int i;
	int x[NUM];
	printf(" Input integer number %d times \n", NUM);
	for (i = 0; i < NUM; i++) {
		printf("x[%d]:", i);
		scanf_s("%d", &x[i]);
	}
	heapsort(x, NUM);
	printf("Sorting is finished \n");
	for (i = 0; i < NUM; i++)
		printf("x[%d] =%d\n", i, x[i]);
	printf("Number of comparison=%d\n", count0);
	printf("Number of swap=%d\n", count1);
	printf("Number of insertion=%d\n", count2);

	return 0;
}

void downheap(int a[], int left, int right) {/* ダウンヒープ関数　*/
											 /* leftからrightまでをヒープ化　*/
											 /* 前提: a[left+1]～a[right]はヒープ済み */
	int temp = a[left];
	int child;
	int parent;

	for (parent = left; parent < (right + 1) / 2; parent = child) {
		int cl = parent * 2 + 1;  /* left child 左の子　*/
		int cr = cl + 1;  /* right child 右の子　*/
		if (cr <= right && a[cr] > a[cl]) { child = cr; count0 += 2; }
		else { child = cl; count0 += 2; } /* 子の大きい方を選択　*/
		if (temp >= a[child]) break; /* 子が小さい場合　ループから抜ける　*/
		a[parent] = a[child]; /* 子の値を親に代入　*/

	}
	a[parent] = temp;/* a[left]をヒープが成立する位置に挿入　*/
	count2++;
}

void heapsort(int a[], int n) {
	int i;

	for (i = (n - 1) / 2; i >= 0; i--)
		downheap(a, i, n - 1);/* 配列初期化　*/

	for (i = n - 1; i > 0; i--) { /* ダウンヒープの繰り返し　*/
		swap(int, a[0], a[i]); count1++;
		downheap(a, 0, i - 1);
	}
}