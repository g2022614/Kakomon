#include <stdio.h>
#define swap(type,x,y) {type t=x; x=y; y=t;}
#define NUM 5
/* count0:比較回数, count1:交換回数 */
int count0 = 0, count1 = 0; /* グローバル変数として初期化　*/
void selsort(int a[], int n); /* 関数プロトタイプ　*/

int main(void){
	int i,x[NUM];

	printf("Input integer number %d times \n", NUM);
	for (i = 0; i<NUM; i++) {
		printf("x[%d]:", i);
		scanf_s("%d", &x[i]);
	}
	selsort(x, NUM);
	printf("Sorting is finished \n");
	for (i = 0; i<NUM; i++)
		printf("x[%d] =%d\n", i, x[i]);
	printf("Number of comparison=%d\n", count0);
	printf("Number of swap=%d\n", count1);

	return 0;
}

void selsort(int a[], int n){
	int i, j, min;

	for (i = 0; i <= n - 1; i++) {
		min = i;
		for (j = i + 1; j <= n - 1; j++) {
			if (a[j]<a[min]) {
				count0++;
				min = j;
			}
			else 
				count0++;
		}
		swap(int, a[i], a[min]);
		count1++;
	}
}