#include <stdio.h>
#include <math.h>

int main(void){

	int i, sum = 0;
	int N[10 ^ 8];

	for (i = 0; i < N[10 ^ 8] + 1; i++){
		sum = sum + N[i];
	}
	printf("%d\n", sum);

	return(0);
}