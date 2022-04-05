// Reference: https://zxi.mytechroad.com/blog/dynamic-programming/leetcode-322-coin-change/
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

int cmpFunction(const void *a, const void *b)
{
	return *(int *)b - *(int *)a;
}

void recursionCoinChange(int *coins, int coinsSize, int amount, int index, int cnt, int *res)
{
	if (amount == 0)
	{
		*res = MIN(*res, cnt);
		return;
	}
	if (index == coinsSize)
		return;

	int i, tmp = coins[index];
	for (i = amount / tmp; i >= 0 && i < *res - cnt; i--)
		recursionCoinChange(coins, coinsSize, amount - i * tmp, index + 1, cnt + i, res);
}

int coinChange(int *coins, int coinsSize, int amount)
{
	if (amount == 0)
		return 0;
	qsort(coins, coinsSize, sizeof(int), cmpFunction);
	int res = INT_MAX;
	recursionCoinChange(coins, coinsSize, amount, 0, 0, &res);
	return res == INT_MAX ? -1 : res;
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