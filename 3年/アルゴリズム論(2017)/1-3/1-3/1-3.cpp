#include <stdio.h>
int main(void){
	int i, n;
	int N = 500;
	int prime[500];
	int ptr = 0;
	int counter = 0;
	int flag;
	prime[ptr++] = 2;
	prime[ptr++] = 3;

	for (n = 5; n <= N; n += 2) {
		flag = 0;
		for (i = 1; counter++, prime[i] * prime[i] <= n; i++) {
			counter++;
			if (n%prime[i] == 0) {
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			prime[ptr++] = n; 
	}
	for (i = 0; i<ptr; i++) printf("%d\n", prime[i]);
	printf("Total number of calculation : %d\n", counter);

	return(0);
}