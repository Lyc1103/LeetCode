#include <stdio.h>
#include <stdlib.h>

_Bool isUgly(int n)
{
	if (n <= 0)
		return 0;
	while (n % 5 == 0)
		n /= 5;
	while (n % 3 == 0)
		n /= 3;
	while (n % 2 == 0)
		n /= 2;
	return n == 1;
}

int main()
{
	int n = 14;
	if (isUgly(n))
		puts("true");
	else
		puts("false");

	return 0;
}