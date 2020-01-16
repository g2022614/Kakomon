/*オイラー法による常微分方程式*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define true 1
#define false 0
#pragma warning(disable:4996)

float x0, yy0, y[101];
int n;

void euler(float h, int n);
float f(float x, float y);

int main(void) {
	float h, xx;
	int j;
	FILE *outfile;

	if ((outfile = fopen("result.csv", "w")) == NULL) {
		fprintf(stderr, "Can not open file \n");
		exit(2);
	}

	printf("\n\n 初期値のx座標とy座標を入力してください \n");
	scanf_s("%f %f", &x0, &yy0);
	printf("解を求めるx座標の上限を入力してください \n");
	scanf_s("%f", &xx);
	printf("区間の分割数を入力してください \n");
	scanf_s("%d", &n);
	h = (xx - x0) / n;

	euler(h, n);

	printf("\n            x                              y \n\n");
	for (j = 0; j <= n; j++) {
		fprintf(outfile, "%15.7e, %15.7e \n", x0 + h*j, y[j]);
		printf("     %15.7e                %15.7e \n", x0 + h*j, y[j]);
	}
	fclose(outfile);
}

float f(float x, float y) {
	float w;

	w = y/(2.0*x);
	return w;
}

void euler(float h, int n) {
	int j;

	y[0] = yy0;
	for (j = 1; j <= n; j++) {
		y[j] = y[j - 1] + h*f(x0 + h*(j - 1), y[j - 1]);
	}
}