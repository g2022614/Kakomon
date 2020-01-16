#include <stdio.h>
int main(void)
{
	int i, n,z;
	int N[5] = { 10,50,100,500,1000 };
	int counter[5] = {};

	for (z = 0; z < 5; z++) {
		for (n = 2; n <= N[z]; n++) {
			for (i = 2; i < n; i++) {
				counter[z]++;
				if (n%i == 0)
					break;
			}
			
		}

		printf("N = %d : %d\n",N[z], counter[z]);
	}

	return(0);
}