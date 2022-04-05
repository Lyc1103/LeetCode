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

int change(int amount, int *coins, int coinsSize)
{
	int i, j, tmp;
	int *dp = (int *)calloc(amount + 1, sizeof(int));
	dp[0] = 1;
	for (i = 0; i < coinsSize; i++)
	{
		tmp = coins[i];
		for (j = tmp; j <= amount; j++)
			dp[j] += dp[j - tmp];
	}
	return dp[amount];
}

int main()
{
	int coins[100] = {0}, coinsSize = 0, amount;
	FILE *pfile = NULL;
	if ((pfile = fopen("518.txt", "r")) == NULL)
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
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d ", &amount);
	printf(" %d ", amount);
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
	puts("");
	printf("coins = ");
	printArray(coins, coinsSize);
	printf("amount = %d\n", amount);

	printf("numbers of changing methods = %d\n", change(amount, coins, coinsSize));

	return 0;
}