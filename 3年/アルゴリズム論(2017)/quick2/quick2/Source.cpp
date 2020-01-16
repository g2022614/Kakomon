#include <stdio.h>
#define swap(type,x,y) do {type t=x; x=y; y=t;} while(0)
#define NUM 5

void quick(int a[], int left, int right); /* 関数プロトタイプ　*/
int count0 = 0, count1 = 0; /* count0:比較回数, count1:交換回数 */

int main(void){
	int i;
	int x[NUM];
	
	printf("Input integer number %d times \n", NUM);
	for (i = 0; i<NUM; i++) {
		printf("x[%d]:", i);
		scanf_s("%d", &x[i]);
	}
	
	quick(x, 0, NUM - 1);
	
	printf("Sorting is finished \n");
	for (i = 0; i<NUM; i++)
		printf("x[%d] =%d\n", i, x[i]);
	printf("Number of comparison=%d\n", count0);
	printf("Number of swap=%d\n", count1);
	
	return 0;
}

void quick(int a[], int left, int right) {
	int pl = left;
	int pr = right;
	int x = a[(pl + pr) / 2]; /* ピボット */
	
	do {
		while (a[pl] < x) {
			pl++;
			count0++;  /*左カーソル移動*/
		}
		count0++;
		while (a[pr] > x) {
			pr--;
			count0++;
		} /*右カーソル移動*/
		count0++;
		if (pl <= pr) {
			swap(int, a[pl], a[pr]); /* 交換　*/
			pl++;
			pr--;
			count1++;
		}
	} while (pl <= pr); /* 左カーソル≦右カーソル　*/
	if (left < pr)
		quick(a, left, pr); /* 再帰呼び出し　*/
	if (pl < right)
		quick(a, pl, right); /* 再帰呼び出し　*/

}