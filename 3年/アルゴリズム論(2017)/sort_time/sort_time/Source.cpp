#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 100000
#define swap(type,x,y) do {type t=x; x=y; y=t;} while(0)

void bubble(int a[], int n);
void selsort(int a[], int n);
void insertion(int a[], int n);
void quick(int a[], int left, int right);
void downheap(int a[], int left, int right);
void heap(int a[], int n);

int main(void) {
	int i, j, x0[NUM], x1[NUM], x2[NUM], x3[NUM], x4[NUM];
	double temp, dt0 = 0.0, dt1 = 0.0, dt2 = 0.0, dt3 = 0.0, dt4 = 0.0;
	time_t start, end;
	srand(time(NULL));

	for (i = 0; i < NUM; i++) {
		temp = (double)rand() / (double)RAND_MAX;
		x0[i] = x1[i] = x2[i] = x3[i] = x4[i] = (int)(temp*1000.0);
	}

	start = clock();
	bubble(x0, NUM);
	end = clock();
	dt0 += (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	selsort(x1, NUM);
	end = clock();
	dt1 += (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	insertion(x2, NUM);
	end = clock();
	dt2 += (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	quick(x3,0,NUM-1);
	end = clock();
	dt3 += (double)(end - start) / CLOCKS_PER_SEC;

	start = clock();
	heap(x4, NUM);
	end = clock();
	dt4 += (double)(end - start) / CLOCKS_PER_SEC;

	printf("Running time bsort=%lf (sec), ssort=%lf (sec),isort = %lf(sec)\n", dt0, dt1, dt2);
	printf("Running time qsort=%lf (sec), hsort=%lf (sec) \n", dt3, dt4);

	return 0;
}

void bubble(int a[], int n){

	for (int i = 0; i<n - 1; i++) {
		for (int j = n - 1; j>i; j--) {
			if (a[j - 1]>a[j])
				swap(int, a[j - 1], a[j]);
		}
	}
}
void selsort(int a[], int n){
	int  min;

	for (int i = 0; i <= n - 1; i++) {
		min = i;
		for (int j = i + 1; j <= n - 1; j++) {
			if (a[j]<a[min]) {
				min = j;
			}
			swap(int, a[i], a[min]);
		}
	}
}

void insertion(int a[], int n){
	int j,tmp;

	for (int i = 1; i <= n - 1; i++) {
		tmp = a[i];
		j = i;
		while ((a[j - 1]>tmp) && (j>0)) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = tmp;
	}
}

void quick(int a[], int left, int right){
	int pl = left,pr = right,x = a[(pl + pr) / 2];

	do {
		while (a[pl]<x) 
			pl++; 
		while (a[pr]>x)
			pr--; 
		if (pl <= pr) {
			swap(int, a[pl], a[pr]);
			pl++;
			pr--;
		}
	} while (pl <= pr);
	
	if (left<pr)
		quick(a, left, pr);
	if (pl<right) 
		quick(a, pl, right);
}

void downheap(int a[], int left, int right){
	int temp = a[left],child,parent;

	for (parent = left; parent < (right + 1) / 2; parent = child) {
		int cl = parent * 2 + 1;
		int cr = cl + 1;
		if (cr <= right && a[cr]>a[cl]) 
			child = cr;
		else 
			child = cl;
		if (temp >= a[child])
			break;
		a[parent] = a[child];
	}
	a[parent] = temp;
}

void heap(int a[], int n) {

	for (int i = (n - 1) / 2; i >= 0; i--)
		downheap(a, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap(int, a[0], a[i]);
		downheap(a, 0, i - 1);
	}
}