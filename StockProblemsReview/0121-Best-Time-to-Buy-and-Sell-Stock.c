#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
	if (pricesSize <= 1)
		return 0;

	int profit = 0, min = prices[0];
	for (int i = 0; i < pricesSize; i++)
	{
		if (profit < prices[i] - min)
			profit = prices[i] - min;
		if (min > prices[i])
			min = prices[i];
	}

	return profit;
}

int main()
{
	int priceSize = 6;
	int prices[6] = {7, 6, 5, 4, 3, 2};
	int profit = maxProfit(prices, priceSize);
	printf("profit = %d\n", profit);

	return 0;
}