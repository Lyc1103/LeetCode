// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/1569081/
#include <stdio.h>

int maxProfit(int *prices, int pricesSize)
{
	if (pricesSize == 0)
		return 0;

	int buy_1 = -prices[0];
	int sell_1 = buy_1 + prices[0];
	int buy_2 = sell_1 - prices[0];
	int sell_2 = prices[0] + buy_2;
	int i, tmp;
	for (i = 1; i < pricesSize; i++)
	{
		// The maximum money left after buying 1st stock.
		// max(第一筆交易買進後所剩的利潤)
		buy_1 = buy_1 > (tmp = -prices[i]) ? buy_1 : tmp;

		// The maximum money left after selling 1st stock.
		// max(第一筆交易賣出後所有的利潤)
		sell_1 = sell_1 > (tmp = buy_1 + prices[i]) ? sell_1 : tmp;

		// The maximum money left after buying 2nd stock.
		// max(第二筆交易買進後所剩的利潤)
		buy_2 = buy_2 > (tmp = sell_1 - prices[i]) ? buy_2 : tmp;

		// The maximum money left after selling 2nd stock.
		// max(第二筆交易賣出後所有的利潤)
		sell_2 = sell_2 > (tmp = buy_2 + prices[i]) ? sell_2 : tmp;
	}

	return sell_1 > sell_2 ? sell_1 : sell_2;
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