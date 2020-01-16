#include <stdio.h>

int cnt = 0;

void move(int no, int x, int y) {

	cnt++;

	if (no > 1)
		move(no - 1, x, 6 - x - y);
	printf("\n[%d]%d=>%d", no, x, y);
	if (no > 1)
		move(no - 1, 6 - x - y, y);

}

int main(void){
	int n;

	printf("No of Disc :");
	scanf_s("%d", &n);
	move(n, 1, 3);
	printf("\n\ncnt = %d\n",cnt);

	return 0;
}