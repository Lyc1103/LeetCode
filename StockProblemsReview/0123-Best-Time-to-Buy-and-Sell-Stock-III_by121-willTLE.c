#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
	int i, j, tmp, min;
	int profit_1 = 0, profit_2 = 0, profit;
	int max_profit = (tmp = prices[pricesSize - 1] - prices[0]) > 0 ? tmp : 0;
	for (i = 0; i < pricesSize; i++)
	{
		profit = 0;
		profit_1 = 0;
		profit_2 = 0;
		min = prices[0];
		for (j = 1; j < i; j++)
		{
			if (profit_1 < prices[j] - min)
				profit_1 = prices[j] - min;
			if (min > prices[j])
				min = prices[j];
		}
		profit = 0;
		min = prices[i];
		for (j = i + 1; j < pricesSize; j++)
		{
			if (profit_2 < prices[j] - min)
				profit_2 = prices[j] - min;
			if (min > prices[j])
				min = prices[j];
		}

		max_profit = max_profit > (tmp = profit_1 + profit_2) ? max_profit : tmp;
		printf("price[%d] = %d, profit_1 = %d, profit_2 = %d, max_profit = %d\n", i, prices[i], profit_1, profit_2, max_profit);
	}
	return max_profit;
}

int main()
{
	int prices[100] = {0}, priceSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("123.txt", "r")) == NULL)
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