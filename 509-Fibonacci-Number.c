#include <stdio.h>
#include <stdint.h>

int fib(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int cur = 1, pre = 0, tmp;
	for (int8_t i = 2; i <= n; i++)
	{
		tmp = cur;
		cur = cur + pre;
		pre = tmp;
		printf("fib(%d) = %d\n", i, cur);
	}
	return cur;
}

int main()
{
	int n = 4;
	printf("fib(%d) = %d\n", n, fib(n));
	return 0;
}