#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) (a < b ? a : b)

int numSquares(int n)
{
	int i, j;
	int dp[10001];
	dp[0] = 0;
	for (i = 1; i <= n; i++)
	{
		dp[i] = i;
		for (j = 1; j * j <= i; j++)
			dp[i] = MIN(dp[i], dp[i - j * j] + 1);
	}
	return dp[n];
}

int main()
{
	int n;
	FILE *pfile = NULL;
	if ((pfile = fopen("279.txt", "r")) == NULL)
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
	printf("num square of %d = %d\n", n, numSquares(n));
	return 0;
}