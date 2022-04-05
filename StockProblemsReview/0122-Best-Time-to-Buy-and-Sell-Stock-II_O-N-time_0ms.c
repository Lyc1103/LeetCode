// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/1569081/
#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
	int i, max_profit = 0, tmp;
	for (i = 1; i < pricesSize; i++)
		if (prices[i] > (tmp = prices[i - 1]))
		{
			// Checking if we can profit with previous day's price.
			// If yes, then we buy on previous day and sell on current day.
			// Add all such profits to get the total profit.
			max_profit += prices[i] - tmp;
		}
	return max_profit;
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