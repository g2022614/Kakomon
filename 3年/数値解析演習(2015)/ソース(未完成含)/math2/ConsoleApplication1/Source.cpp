/* 5/1 ���l��͉��K�@��3 256129 kei sugiura */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define i 3
#define j 3

int main(void){
	int A[i][j];
	int B[i][j];
	int AB[i][j];
	int x, y;
	int Alarge[i] = { { 0 } }, Blarge[i] = { { 0 } }, ABlarge[i] = { { 0 } };
	int Asum = 0, Bsum = 0, ABsum = 0;
	printf("A��3�s3�����͂��Ă�������\n");
	for (x = 1; x <= i; x++){
		for (y = 1; y <= j; y++){
			scanf_s("%d", &A[x][y]);
		}
	}
	printf("B��3�s3�����͂��Ă�������\n");
	for (x = 1; x <= i; x++){
		for (y = 1; y <= j; y++){
			scanf_s("%d", &B[x][y]);
		}
	}
	
	/*A,B�\��,�m�����v�Z*/
	printf("A=\n");
	for (x = 1; x <= i; x++){
		for (y = 1; y <= j; y++){
			printf("%d ", A[x][y]);
			if (Alarge[x] < abs(A[x][y])) Alarge[x] = abs(A[x][y]);
		}
		printf("\n");
	}
	printf("B=\n");
	for (x = 1; x <= i; x++){
		for (y = 1; y <= j; y++){
			printf("%d ", B[x][y]);
			if (Blarge[x] < abs(B[x][y])) Blarge[x] = abs(B[x][y]);
		}
		printf("\n");
	}
	
	for (x = 1; x <= i; x++){
		for (y = 1; y <= j; y++){
			AB[x][y] = A[x][y] + B[x][y];
			if (ABlarge[x] < abs(AB[x][y])) ABlarge[x] = abs(AB[x][y]);
		}
	}
	/*���A,B���v�v�Z,�\��*/
	for (x = 1; x <= i; x++){
		Asum += Alarge[x];
		Bsum += Blarge[x];
		ABsum += ABlarge[x];
	}
	printf("A�̃m������%d+%d+%d=%d\n", Alarge[1], Alarge[2], Alarge[3], Asum);
	printf("B�̃m������%d+%d+%d=%d\n", Blarge[1], Blarge[2], Blarge[3], Bsum);
	printf("A��B�𑫂����x�N�g���m������%d+%d+%d=%d\n", ABlarge[1], ABlarge[2], ABlarge[3], ABsum);

	printf("||AB|| <= ||A|| + ||B|| �́@%d <= %d + %d �ƂȂ�", ABsum, Asum, Bsum);

	return 0;
}