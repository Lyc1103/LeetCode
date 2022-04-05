#include <stdio.h>
#include <stdint.h>

int tribonacci(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	if (n == 2)
		return 1;

	int cur = 1, pre = 1, prepre = 0, tmp;
	for (int8_t i = 3; i <= n; i++)
	{
		tmp = cur;
		cur = cur + pre + prepre;
		prepre = pre;
		pre = tmp;

		printf("tribonacci(%d) = %d\n", i, cur);
	}
	return cur;
}

int main()
{
	int n = 25;
	printf("tribonacci(%d) = %d\n", n, tribonacci(n));
	return 0;
}