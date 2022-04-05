// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/discuss/1569081/
#include <stdio.h>

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

int maxProfit(int *prices, int pricesSize, int fee)
{
	if (pricesSize == 0)
		return 0;

	int buy = -prices[0];
	int sell = 0;
	int i, tmp;
	for (i = 1; i < pricesSize; i++)
	{
		buy = buy > (tmp = sell - prices[i]) ? buy : tmp;
		sell = sell > (tmp = buy + prices[i] - fee) ? sell : tmp;
	}

	return sell;
}

int main()
{
	int prices[100] = {0}, priceSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("714.txt", "r")) == NULL)
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

	int fee = prices[--priceSize];
	printf("fee = %d, input array = ", fee);
	printArray(prices, priceSize);
	int profit = maxProfit(prices, priceSize, fee);
	printf("profit = %d\n", profit);

	return 0;
}