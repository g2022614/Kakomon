
#include <stdio.h>
#include <math.h>

int main(void)
{

	float x=1.0,result=0.0;
	/* (1) */
	for (int i = 0; i < 10; i++){
		result = (sqrt(1+x) - 1) / sqrt(1+x);
		printf("result:%e\n", result);
		x = x / 10;

	}
	printf("\n");
	x = 1.0;
	result = 0.0;

	/* (2) */
	for (int i = 0; i < 10; i++){
		result = x / ((x + 1) + sqrt(x + 1));
		printf("result:%e\n", result);
		x = x / 10;

	}

	return(0);
}
