#include <stdio.h>
#include <stdlib.h>

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

int maxProfit(int *prices, int pricesSize)
{
	if (pricesSize <= 1)
		return 0;

	int i, j, k, l, tmp;
	int *dp = (int *)calloc(pricesSize, sizeof(int));
	for (i = 0; i < pricesSize; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (j > 0)
			{
				printf("here1: ");
				dp[i] = dp[i] > (tmp = prices[i] - prices[j] + dp[j - 1]) ? dp[i] : tmp;
			}
			else
			{
				printf("here2: ");
				dp[i] = dp[i - 1] > (tmp = prices[i] - prices[j]) ? dp[i - 1] : tmp;
			}
			printf("i = %d, j = %d, price[%d] = %d, price[%d] = %d, dp[%d] = %d\n", i, j, i, prices[i], j, prices[j], i, dp[i]);
		}
	}
	printArray(dp, pricesSize);
	free(dp);
	return dp[pricesSize - 1];
}

int main()
{
	int prices[100] = {0}, priceSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("122.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &prices[priceSize]);
		printf("%d ", prices[priceSize]);
		priceSize++;
	}
	puts("");

	int profit = maxProfit(prices, priceSize);
	printf("profit = %d\n", profit);

	return 0;
}