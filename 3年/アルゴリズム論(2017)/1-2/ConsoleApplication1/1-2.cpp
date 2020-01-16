#include <stdio.h>
int main(void){
	int i, n;
	int N = 500;
	int prime[500];
	int ptr = 0;
	int counter = 0;

	prime[0] = 2;
	ptr++;

	for (n = 3; n <= N; n += 2) {
		for (i = 1; i<ptr; i++) {
			counter++;
			if (n%prime[i] == 0)
				break;
		}
		if (ptr == i)
			prime[ptr++] = n;
	}
	
	for (i = 0; i<ptr; i++)
		printf("%d\n", prime[i]);
	printf("Total number of calculation : %d\n", counter);
	
	return(0);
}