#include<stdio.h>
#include<math.h>
#define SIZE 4
#define LEVEL 8

int main(void) {

	//テスト仮想画像配列
	int test[SIZE][SIZE] = { {0,2,2,7},
				{0,2,3,7},
				{1,1,5,7},
				{1,1,6,7} };

	//画素/レベルを求める
	int piclv = (SIZE * SIZE) / LEVEL;

	//濃度を数えるための配列
	int noudo[LEVEL] = {};

	//カウント変数
	int i, j, k;

	//計算に使用
	int wa = 0;
	//int div = 0; 
	int move[LEVEL] = {};

	//処理前の表示
	printf("〜処理前〜\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%d  ", test[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	printf("画素/レベル：%d\n", piclv);
	printf("\n");

	//濃度をカウント
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			noudo[test[i][j]]++;
		}
	}

	//濃度を表示
	printf("〜各レベル濃度の個数〜\n");
	for (i = 0; i < LEVEL; i++) {
		printf("%dレベル：%d個\n", i, noudo[i]);
	}
	printf("\n");

	//画素の移動計算部分
	printf("〜順位付け（その画素までの和）〜\n");
	for (i = 0; i < LEVEL; i++) {

		/*move[i] = div;
		  wa += noudo[i];
		  div = wa / piclv;*/

		if (i == 0) 
			move[i] = 0;		

		else {
			wa += noudo[i - 1];
			move[i] = wa / piclv;
		}

		printf("%dレベル：%2d（位）\n", i, wa);
	}

	printf("\n");

	printf("~画素の移動~\n");
	for (i = 0; i < LEVEL; i++) {
		printf("%dレベル：%dに移動\n", i, move[i]);
	}

	//画素の更新
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			for (k = 0; k < LEVEL; k++) {
				if (k == test[i][j]) {
					test[i][j] = move[k];
					break;
				}
			}
		}
	}
	printf("\n");

	//処理後の表示
	printf("〜処理後〜\n");
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			printf("%d  ", test[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}