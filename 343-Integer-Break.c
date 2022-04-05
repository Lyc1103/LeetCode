#include <stdio.h>

int integerBreak(int n)
{
	if (n == 2)
		return 1;
	if (n == 3)
		return 2;
	if (n == 4)
		return 4;
	if (n == 5)
		return 6;
	if (n == 6)
		return 9;

	int dp[3] = {0};
	dp[0] = 4;
	dp[1] = 6;
	dp[2] = 9;
	for (int i = 7; i <= n; i += 3)
	{
		dp[0] *= 3;
		dp[1] *= 3;
		dp[2] *= 3;
	}
	if (n % 3 == 1)
		return dp[0];
	if (n % 3 == 2)
		return dp[1];
	if (n % 3 == 0)
		return dp[2];
	return 0;
}

int main()
{
	int n;
	FILE *pfile = NULL;
	if ((pfile = fopen("343.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &n);
	printf(" %d ", n);
	puts("");
	printf("max product of %d = %d\n", n, integerBreak(n));
	return 0;
}