#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) (a < b ? a : b)

int numsChange(int *nums, int numsSize, int n)
{
	int i, j, tmp;
	int *dp = (int *)calloc(n + 1, sizeof(int));
	for (j = 1; j <= n; j++)
		dp[j] = INT_MAX;
	for (i = 0; i < numsSize; i++)
	{
		for (j = nums[i]; j <= n; j++)
		{
			tmp = j - nums[i];
			if (dp[tmp] != INT_MAX)
				dp[j] = MIN(dp[j], dp[tmp] + 1);
		}
	}
	return dp[n] == INT_MAX ? -1 : dp[n];
}

int numSquares(int n)
{
	int i, tmp;
	int buffer[101], cnt = 0;
	for (i = 0; i * i < n; i++)
	{
		buffer[i] = i * i;
	}
	if (i * i == n)
		return 1;
	return numsChange(buffer, i, n);
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