/*���R�r�@�ɂ��A���ꎟ�������̉�*/

#include<stdio.h>
#include<math.h>
#define N 3
#define EPSILON 1.0E-5

float a[N][N] = { { 5.0, 2.0, 1.0 }, { 1.0, 4.0, 2.0 }, { 2.0, 1.0, 4.0 } };
float b[N] = { 17.0, 16.0, 11.0 };

int k;
float x[N];

void jacobi();

int main(void){
	int i, j;

	jacobi();

	printf("\n\n  =====  �W���s��ƒ萔  =====  \n\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%10.4f", a[i][j]);
		}
		printf("      %10.4f\n", b[i]);
	}

	jacobi();

	printf("\n\n =====  ���R�r�@�ɂ��A���ꎟ�������̉�  ===== \n\n");
	printf("�J��Ԃ� = %d\n\n", k);
	for (i = 0; i < N; i++){
		printf(" x[%d] = %10.4f \n", i + 1, x[i]);
	}
	return 0;
}

void jacobi(){
	int i, j;
	float Nk, xx, xdif;
	float x0[N];

	k = 0;
	for (i = 0; i < N; i++){ x[i] = 0.0; }
	do{
		k = k + 1;
		Nk = 0.0;
		for (i = 0; i < N; i++){ x0[i] = x[i]; }
		for (j = 0; j < N; j++){
			xx = b[j];
			for (i = 0; i < N; i++)
				if (i != j) xx = xx - a[j][i] * x0[i];
				x[j] = xx / a[j][i];
				xdif = x[j] - x0[j];
				if (xdif < 0.0) xdif = -xdif;
				Nk = Nk + xdif;
		}
	} while (Nk > EPSILON);
}
