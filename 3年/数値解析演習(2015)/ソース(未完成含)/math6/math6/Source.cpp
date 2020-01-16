/*オイラー法による常微分方程式*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define true 1
#define false 0
#pragma warning(disable:4996)
/*x0,y0,x1,y1だとエラーがでるためx2,y2とする*/
float x2, y2, y[101];
int n;

void euler(float h, int n);

int main(void){
	float h, xx;
	int j;
	FILE *outfile;

	if ((outfile = fopen("result.csv", "w")) == NULL){
		fprintf(stderr, "Can not open file \n");
		exit(2);
	}

	printf("\n\n 初期値のx座標とy座標を入力してください \n");
	scanf_s("%f %f", &x2, &y2);
	printf("解を求めるx座標の上限を入力してください \n");
	scanf_s("%f", &xx);
	printf("区間の分割数を入力してください \n");
	scanf_s("%d", &n);
	h = (xx - x2) / n;

	euler(h, n);

	printf("\n            x                              y \n\n");
	for (j = 0; j <= n; j++){
		fprintf(outfile, "%15.7e, %15.7e \n", x2 + h*j, y[j]);
		printf("     %15.7e                %15.7e \n", x2 + h*j, y[j]);
	}
	fclose(outfile);
}

float f(float x, float y);
float f(float x, float y){
	int i;
	float w;

	w = ( x * x ) - 2 * (1 + x) * y;
	return w;
}

void euler(float h, int n){
	int j;
	float s;

	y[0] = y2;
	for (j = 1; j <= n; j++){
		y[j] = y[j - 1] + h*f(x2 + h*(j - 1), y[j - 1]);
	}
}