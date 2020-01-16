
/*�|�o�@�ɂ��A���ꎟ�������̉�*/

#include <stdio.h>
#include <math.h>
#define N 3
#define EPSILON 1.0E-5
#define TRUE 1
#define FALSE 0

/*�s�񏉊��ݒ�*/
float a[N][N] = { { 4.0, -1.0, -2.0 }, { 1.0, 0.0, -1.0 }, { 0.0, -3.0, 8.0 } };
float x[N];
float b[N] = { 1.0, 0.0, 1.0 };

int sw;
void sweep(int *sw); /*�|�o*/
void swap(float *wk1, float *wk2); /*���֊֐�*/

int main(void){
	int i, j;

	printf(" =====  �W���s��ƒ萔  =====\n\n");
	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){ printf("%10.4f", a[i][j]); }
		printf("%10.4f\n\n", b[i]);
	}
	sw = TRUE;

	sweep(&sw);


	if (sw == TRUE){
		printf("\n\n ===== �|�o�@�ɂ��A���ꎟ�������̉� ===== \n\n");
		for (i = 0; i < N; i++){ printf(" x[%d] = %10.4f \n", i + 1, x[i]); }
	}
	else printf("���͋��߂��܂���ł����B\n\n");
	return 0;
}

void swap(float *wk1, float *wk2){
	float w;
	w = *wk1;
	*wk1 = *wk2;
	*wk2 = w;
}


void sweep(int *sw){
	int i, j, k, ik;
	float ak, aik;

	for (k = 0; k < N; k++){
		ak = a[k][k];
		if (fabs(ak) <= EPSILON){
			ik = k + 1;
			while ((ik < N) && (fabs(a[ik][k]) < EPSILON)) ik++;
			if (ik < N){
				for (j = k; j < N; j++){ swap(&a[k][j], &a[ik][j]); }
				swap(&b[k], &b[ik]);
				ak = a[k][k];
			}
			else
			{
				printf(" �s�{�b�g����ł� !  \n");
				*sw = FALSE;
			}
		}
		for (j = k; j < N; j++){
			a[k][j] = a[k][j] / ak; /*k�s�̏���*/
			b[k] = b[k] / ak;
		}
		for (i = 0; i < N; i++){
			if (i != k){
				aik = a[i][k];
				for (j = k; j < N; j++){
					a[i][j] = a[i][j] - aik*a[k][j];
					b[i] = b[i] - b[k] * aik;
				}
			}
		}
		for (k = 0; k < N; k++){ x[k] = b[k]; }
	}
}
