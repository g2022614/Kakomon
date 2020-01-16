/*ヤコビ法による連立一次方程式の解*/
/*数値解析法演習レポート課題3　課題1問目*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define N 4
#define EPSILON 1.0E-5

float a1[N][N] ={
	{ 4.0, 1.0, 1.0, 1.0 },
	{ 1.0, 4.0, 1.0, 1.0 },
	{ 1.0, 1.0, 4.0, 1.0 },
	{ 1.0, 1.0, 1.0, 4.0 } };
float a2[N][N] = {
	{ 3.0, 1.0, 1.0, 1.0 },
	{ 1.0, 3.0, 1.0, 1.0 },
	{ 1.0, 1.0, 3.0, 1.0 },
	{ 1.0, 1.0, 1.0, 3.0 } };
float a3[N][N] = {
	{ 2.99, 1.0, 1.0, 1.0 },
	{ 1.0, 2.99, 1.0, 1.0 },
	{ 1.0, 1.0, 2.99, 1.0 },
	{ 1.0, 1.0, 1.0, 2.99 } };

float b[N] = { 1.0, 0.0, 1.0, 0.0 };

int k;
float x[N]; /*ek*/

void jacobi();

int main(void){
	int i, j;

	printf("\n\n =====  係数行列と定数  ===== \n\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%10.4f", a1[i][j]);
		}
		printf("      %10.4f\n", b[i]);
	}

	jacobi();

	printf("\n\n =====  ヤコビ法による連立一次方程式の解  ===== \n\n");
	printf("繰り返し = %d\n\n", k);
	for (i = 0; i < N; i++){
		printf(" x[%d] = %10.4f \n", i + 1, x[i]);
	}
	return 0;
}

void jacobi(){
	int i, j;
	float Nk, xx, xdif;
	float x0[N];
	FILE *outfile,*fp;

	/*** Open output file ***/
	if ((outfile = fopen("result3.csv", "w")) == NULL){
		fprintf(stderr, "Can't open file \n");
		exit(2);
	}

	k = 0;
	for (i = 0; i < N; i++){ x[i] = 0.0; }
	do{
		k = k + 1;
		Nk = 0.0;
		for (i = 0; i < N; i++){ x0[i] = x[i]; }
		for (j = 0; j < N; j++){
			xx = b[j];
			for (i = 0; i < N; i++){
				if (i != j) xx = xx - a1[j][i] * x0[i];
			}
				x[j] = xx / a1[j][j];
				xdif = x[j] - x0[j];
				if (xdif < 0.0) xdif = -xdif;
				Nk = Nk + xdif;
			}
		if (k == 50) break;
	fprintf(outfile, "%d, %e\n", k, Nk);
	} while (Nk > EPSILON);
	fclose(outfile);
}
