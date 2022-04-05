// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/1569081/
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

int maxProfit(int k, int *prices, int pricesSize)
{
	if (pricesSize == 0 || k == 0)
		return 0;
	int i, j, tmp;
	int *buy = (int *)calloc(k, sizeof(int));
	int *sell = (int *)calloc(k, sizeof(int));
	buy[0] = -prices[0];
	sell[0] = 0;

	for (i = 1; i < k; i++)
	{
		buy[i] = sell[i - 1] - prices[0];
		sell[i] = 0;
	}

	for (j = 0; j < pricesSize; j++)
	{
		buy[0] = buy[0] > (tmp = -prices[j]) ? buy[0] : tmp;
		sell[0] = sell[0] > (tmp = buy[0] + prices[j]) ? sell[0] : tmp;
		for (i = 1; i < k; i++)
		{
			buy[i] = buy[i] > (tmp = sell[i - 1] - prices[j]) ? buy[i] : tmp;
			sell[i] = sell[i] > (tmp = buy[i] + prices[j]) ? sell[i] : tmp;
		}
	}

	int max_sell = sell[0];
	for (i = 1; i < k; i++)
	{
		max_sell = max_sell > (tmp = sell[i]) ? max_sell : tmp;
	}
	return max_sell;
}

int main()
{
	int prices[100] = {0}, priceSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("188.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &prices[priceSize]);
		printf("%c%d ", c, prices[priceSize]);
		priceSize++;
	}
	puts("");

	int transaction_times = prices[--priceSize];
	printf("transaction_times = %d, input array = ", transaction_times);
	printArray(prices, priceSize);
	int profit = maxProfit(transaction_times, prices, priceSize);
	printf("profit = %d\n", profit);

	return 0;
}