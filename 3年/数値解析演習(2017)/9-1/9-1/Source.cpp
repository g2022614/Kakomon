#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#define N  3
#define N1 N+1
#define M  10
#define TRUE 1
#define FALSE 0

float x[M] = { 0.0,1.0, 2.0, 3.0,4.0,5.0,6.0,7.0,8.0,9.0 },
f[M] = { 1.1, 5.1, 22.0,27.0,48.0,56.0,53.0,75.0,79.0,93.0 },
a[N1][N1], b[N1], c[N1];
int sw;

/*=====================================================================*/
/*** べき乗を求める ***/
float gg(int j,float x)
{
	float wk;
	int i;

	wk = 1.0;
	for (i = 0; i<j; i++) {
		wk = wk*x;
	}
	return(wk);
}

/*=====================================================================*/
/*** x = xxのときの近似多項式の値を求める ***/
float fvalue(float xx)
{
	float wk;
	int i;

	wk = 0.0;
	for (i = 0; i<N1; i++) {
		wk = wk + c[i] * gg(i, xx);
	}
	return(wk);
}

/*=====================================================================*/
/*** 値を入れ替える．（部分ピボット選択法） ***/
void swap(float* wk1,
	float* wk2)
{
	float w;
	w = *wk1; *wk1 = *wk2; *wk2 = w;
}

/*=====================================================================*/
/*** 掃き出し法 ***/
void sweep(int* sw) {
	int i, j, k, ik;
	float ak, aik;
	float EPSILON = 1.0e-5;

	*sw = TRUE;

	for (k = 0; k < N1; k++) {
		ak = a[k][k];

		/*>>> Pivotting ***/
		if (fabs(ak) <= EPSILON) {
			ik = k + 1;
			while ((ik < N1) && (fabs(a[ik][k]) < EPSILON)) ik++;
			if (ik < N1) {
				for (j = k; j < N1; j++) {
					swap(&a[k][j], &a[ik][j]);
				}
				swap(&b[k], &b[ik]);
				ak = a[k][k];
			}
			else {
				printf("pivot is 0 !!\n");
				*sw = FALSE;
				return;
			}
		} /* end if(fabs(ak) <= EPSILON) */
		  /*<<< Pivotting ***/

		for (j = k; j < N1; j++) {
			a[k][j] /= ak;
		}
		b[k] /= ak;

		for (i = 0; i < N1; i++) {
			if (i != k) {
				aik = a[i][k];
				for (j = k; j < N1; j++) {
					a[i][j] -= aik*a[k][j];
				} /* end j */
				b[i] -= aik*b[k];
			} /* end if(i!=k) */
		} /* end i */
	} /* end k */

	for (k = 0; k < N1; k++) {
		c[k] = b[k];
	}
}

/*=====================================================================*/
/*** 最小二乗法 ***/
void leasqr(int* sw)
{
	float wk;
	int i, j, k;

	for (i = 0; i < N1; i++) {
		for (j = i; j < N1; j++) {
			wk = 0.0;
			for (k = 0; k < M; k++) {
				wk += gg(i, x[k]) * gg(j, x[k]);
			}
			a[i][j] = wk;
			a[j][i] = wk;
		}
	}
	for (i = 0; i < N1; i++) {
		wk = 0.0;
		for (k = 0; k < M; k++) {
			wk += gg(i, x[k])*f[k];
		}
		b[i] = wk;
	}
	sweep(sw);
}

/*=====================================================================*/
/*** 近似多項式関数によるデータ列を出力 ***/
void output_result(void) {
	int i;
	double interval;
	double num_point = 51; /* 51点出力 */
	double num_segment;
	double delta;
	FILE *outfile;

	num_segment = num_point - 1;

	/*** Open output file ***/
	if ((outfile = fopen("result.csv", "w")) == NULL) {
		fprintf(stderr, "Can't open file \n");
		exit(2);
	}

	interval = x[M - 1] - x[0];
	delta = interval / num_segment;
	for (i = 0; i < num_point; i++) {
		double xx = x[0] + i * delta;
		double ff = fvalue(xx);
		fprintf(outfile, "%e, %e\n", xx, ff);
	}
	fclose(outfile);
}

/*=====================================================================*/
/*** 元のデータを出力 ***/
void output_data(void) {
	int i;
	FILE *outfile;

	/*** Open output file ***/
	if ((outfile = fopen("data.csv", "w")) == NULL) {
		fprintf(stderr, "Can't open file \n");
		exit(2);
	}

	for (i = 0; i < M; i++) {
		fprintf(outfile, "%e, %e\n", x[i], f[i]);
	}
	fclose(outfile);
}

/*=====================================================================*/
int main(void)
{
	float xx;
	int i;

	sw = TRUE;
	leasqr(&sw);
	output_data();
	output_result();

	if (sw) {
		printf("関数の係数 =\n");
		for (i = 0; i<N1; i++) {
			printf("\n   c[%2d] = %12.6e", i, c[i]);
		}
		for(int j=1;j<11;j++) {
			//printf("\n x の値を入力して下さい。\n");
			//scanf("%f", &xx);
			if ((j >= x[0]) && (j <= x[M - 1])) {
				printf("\n 関数の値 = %e \n", fvalue(j));
			}
			else {
				return 0;
			}
		}
	}
	else {
		printf("\n 近似多項式関数は求められませんでした。\n");
	}
}
