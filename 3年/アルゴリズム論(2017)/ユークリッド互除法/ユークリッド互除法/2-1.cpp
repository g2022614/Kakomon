#include <stdio.h>

int cnt=0;

int gcd(int a, int b){

	cnt++;

	if (b == 0)
		return(a);
	else
		return(gcd(b, a % b));/*　再帰呼び出し　*/

}

int main(void) {
	int a, b;

	printf("input a :");
	scanf_s("%d",&a);
	printf("input b :");
	scanf_s("%d",&b);
	printf("gcd is %d \n", gcd(a, b));
	printf("cnt = %d\n",cnt);

	return 0;
}