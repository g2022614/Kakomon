#include<stdio.h>
#include<math.h>

int main(void) {
	float result = 0, result2 = 0, x = 0.1;
	
	result = (sqrt(1 + x) - 1) / (sqrt(1 + x));
	result2 = x / ((1 + x) + sqrt(1 + x));

	printf("x = %.2f ‚Ì‚Æ‚«\n", x);
	printf("result  = %e\n", result);
	printf("result2 = %e\n\n", result2);

	x = 0.01;

	result = (sqrt(1 + x) - 1) / (sqrt(1 + x));
	result2 = x / ((1 + x) + sqrt(1 + x));

	printf("x = %.2f ‚Ì‚Æ‚«\n", x);
	printf("result  = %e\n", result);
	printf("result2 = %e\n\n", result2);

	return 0;		
}