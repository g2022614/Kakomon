#include<stdio.h>

int main(void){
	int n = 100000000,i;
	float result = 0,result2  = 0, a = 0.1;

	for (i = 1; i <= n; i++)
		result += a;
	result2 = n * a;

	printf("result  = %e\n",result);
	printf("result2 = %e\n",result2);

	return 0;
}