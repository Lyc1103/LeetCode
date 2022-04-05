// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/1569081/
#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
	if (pricesSize == 0)
		return 0;

	int buy = -prices[0];
	int sell = 0;
	int pre_sell = 0;
	int i, tmp;
	for (i = 1; i < pricesSize; i++)
	{
		// buy[i] = Math.max(sell[i-2]-prices[i], buy[i-1])
		// sell[i-2]-prices[i] -> Buy after a 1 day cooldown
		// buy[i-1] -> cooldown
		buy = buy > (tmp = pre_sell - prices[i]) ? buy : tmp;

		// sell[i-1];
		pre_sell = sell;

		// sell[i] = Math.max(buy[i]+prices, sell[i-1])
		// buy[i]+prices -> sell the stock.
		// sell[i-1] -> cooldown
		sell = sell > (tmp = buy + prices[i]) ? sell : tmp;
	}

	return sell;
}

int main()
{
	int prices[100] = {0}, priceSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("309.txt", "r")) == NULL)
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