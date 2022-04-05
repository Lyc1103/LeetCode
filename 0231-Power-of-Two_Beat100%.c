#include <stdio.h>

_Bool isPowerOfTwo(int n)
{
	printf("n = %d\n", n);
	if (n == 0)
		return 0;
	while (n % 2 == 0)
	{
		n /= 2;
		printf("n = %d\n", n);
	}
	return n == 1 ? 1 : 0;
}

int main()
{
	int n = 3;
	if (isPowerOfTwo(n))
		puts("true");
	else
		puts("false");
	return 0;
}