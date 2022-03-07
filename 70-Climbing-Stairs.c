#include <stdio.h>

int climbStairs(int n)
{
	int a_n_2 = 1, a_n_1 = 2;
	if (n == 1)
		return 1;
	if (n == 2)
		return 2;
	for (int i = 3; i <= n; i++)
	{
		int tmp = a_n_1;
		a_n_1 = a_n_1 + a_n_2;
		a_n_2 = tmp;
	}
	return a_n_1;
}

int main()
{
	int n = 3;
	int res = climbStairs(n);
	printf("%d\n", res);
}