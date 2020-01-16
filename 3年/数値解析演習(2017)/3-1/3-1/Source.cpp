/*�|���o���@�ɂ��s��̋t�s��y�эs�񎮂̌v�Z*/
#include <stdio.h>
#include <math.h>
#define N 3
#define N1 6
#define EPSILON 1.0E-5
#define TRUE 1
#define FALSE 0

/*�s�񏉊��ݒ�*/
float a[N][N1] = { { 4.0, -1.0, -2,1.0, 0.0, 0.0 },
				  { 1.0, 0.0, -1.0, 0.0, 1.0, 0.0 },
				  { 0.0, -3.0, 8.0, 0.0, 0.0, 1.0 } };
float det;
int sw;

void sweep(int *sw); /*�|�o*/
void swap(float *wk1, float *wk2); /*���֊֐�*/

int main(void) {
	int i, j;

	printf("\n\n ===== ���̍s�� ===== \n\n");
	for (i = 0; i < N; i++) {
		printf("%d:", i + 1);
		for (j = 0; j < N; j++)
			printf("% 10.4f ", a[i][j]);
		printf("\n");
	}
	printf("\n\n");

	sw = TRUE;

	sweep(&sw);

	if (sw == TRUE) {
		printf("\n\n ===== �t�s�� ===== \n\n");
		for (i = 0; i < N; i++) {
			printf(" %d :", i + 1);
			for (j = N; j < N1; j++)
				printf(" %10.4f ", a[i][j]);
			printf("\n");
		}
		printf("\n �s�� = %8.4f \n", det);
	}
	else 
		printf("\n �t�s��͋��܂�܂���ł��� ! \n");

	return 0;
}

void sweep(int *sw) {
	int i, j, k, ik;
	float ak, aik, p;

	det = 1.0;
	p = 1.0;
	for (k = 0; k < N; k++) {
		ak = a[k][k];
		if (fabs(ak) <= EPSILON) {
			ik = k + 1;
			while ((ik < N) && (fabs(a[ik][k]) < EPSILON))
				ik++;
			if (ik < N) {
				for (j = k; j < N1; j++) 
					swap(&a[k][j], &a[ik][j]);
				ak = a[k][k];
				p = -p;
			}
			if (ik >= N) {
				printf(" �s�{�b�g����ł� !  \n");
				sw = FALSE;
			}
		}
		det = det*ak;
		for (j = k; j < N1; j++) 
			a[k][j] = a[k][j] / ak; /*k�s�̏���*/
		
		for (i = 0; i < N; i++) {
			if (i != k) {
				aik = a[i][k];
				for (j = k; j < N1; j++) 
					a[i][j] = a[i][j] - aik*a[k][j];
			}
		}
	}
	det = p*det;

}

void swap(float *wk1, float *wk2) {
	float w;

	w = *wk1;
	*wk1 = *wk2;
	*wk2 = w;

}