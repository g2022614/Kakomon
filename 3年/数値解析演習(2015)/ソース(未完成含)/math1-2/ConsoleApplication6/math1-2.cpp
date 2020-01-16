#include <stdio.h>
#include <math.h>
#define N 100000000

int main(void){

	int i;
	float x = 0.1;
	float result1 = 0;
	float result2 = 0;

	/*ƒ°‚Ì‚Æ‚«*/
	for (i = 1; i <= N; i++){
		result1 += 0.1;
	}

	printf("result1:%e\n", result1);

	/*0.1N‚Ì‚Æ‚«*/
	for (i = 1; i <= N; i++){
		result2 += 0.1*i;
	}

	printf("result2:%e\n", result2);

	return 0;

}


