#include<stdio.h>

int main(void) {
	int a[3][3] = { {2,3,0},
					{3,-6,1},
					{1,-2,0} };
	int b[3][3] = { { 1,3,0 },
					{ 1,2,1 },
					{ 1,-5,-1 } };
	int max[3][3] = {}, ans[3] = {}, tmp, x[3][3] = {};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (0 > a[i][j])
				tmp = a[i][j] * -1;
			else
				tmp = a[i][j];

			if (tmp > max[0][i])
				max[0][i] = tmp;

			if (0 > b[i][j])
				tmp = b[i][j] * -1;
			else
				tmp = b[i][j];

			if (tmp > max[1][i])
				max[1][i] = tmp;

			x[i][j] = a[i][j] + b[i][j];

			if (0 > x[i][j])
				tmp = x[i][j] * -1;
			else
				tmp = x[i][j];

			if (tmp > max[2][i])
				max[2][i] = tmp;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			ans[i] += max[i][j];
	}

	printf("||A|| = %d\n", ans[0]);
	printf("||B|| = %d\n", ans[1]);
	printf("||A|| + ||B|| = %d\n", ans[2]);

	if (ans[2] < ans[0] + ans[1])
		printf("%d … %d ‚È‚Ì‚Å¬‚è—§‚Â\n", ans[2], ans[0] + ans[1]);
	else
		printf("%d … %d ‚È‚Ì‚Å¬‚è—§‚½‚È‚¢\n", ans[2], ans[0] + ans[1]);

	return 0;
}