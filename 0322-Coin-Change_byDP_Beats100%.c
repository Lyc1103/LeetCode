#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

void printArrayOfDP(int *nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
		printf("%2d ", nums[i]);
	printf("%2d\n", nums[numsSize - 1]);
	return;
}

#define MIN(a, b) (a < b ? a : b)

int coinChange(int *coins, int coinsSize, int amount)
{
	if (amount == 0)
		return 0;
	int i, j, tmp;
	int *dp = (int *)calloc(amount + 1, sizeof(int));
	printf("result matrix =\n     0 ");
	for (j = 1; j <= amount; j++)
	{
		dp[j] = INT_MAX;
		printf("%2d ", j);
	}
	puts("");
	for (i = 0; i < coinsSize; i++)
	{
		for (j = coins[i]; j <= amount; j++)
		{
			tmp = j - coins[i];
			if (dp[tmp] != INT_MAX)
			{
				dp[j] = MIN(dp[j], dp[tmp] + 1);
			}
		}
		printf(" %2d ", coins[i]);
		printArrayOfDP(dp, amount + 1);
	}
	return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main()
{
	int coins[100] = {0}, coinsSize = 0, amount;
	FILE *pfile = NULL;
	if ((pfile = fopen("322.txt", "r")) == NULL)
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
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{

		fscanf(pfile, "%d", &coins[coinsSize]);
		printf("%d", coins[coinsSize]);
		coinsSize++;
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d ", &amount);
	printf(" %d ", amount);
	puts("");
	printf("coins = ");
	printArray(coins, coinsSize);
	printf("amount = %d\n", amount);

	printf("min-coinChange = %d\n", coinChange(coins, coinsSize, amount));

	return 0;
}