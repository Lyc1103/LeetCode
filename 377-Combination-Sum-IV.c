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

void printArrayOfDP(long long *nums, int numsSize)
{
	for (int i = 0; i < numsSize - 1; i++)
		printf("%2d ", nums[i]);
	printf("%2d\n", nums[numsSize - 1]);
	return;
}

int combinationSum4(int *nums, int numsSize, int target)
{
	int i, j, k, tmp;
	long long *dp = (long long *)calloc(target + 1, sizeof(long long));
	dp[0] = 1;
	printf("result matrix =\n     0 ");
	for (j = 1; j <= target; j++)
		printf("%2d ", j);
	puts("");
	for (j = 1; j <= target; j++)
		for (i = 0; i < numsSize && dp[j] < 2147483648; i++)
			if (j - nums[i] >= 0)
				dp[j] += dp[j - nums[i]];
	printf(" -> ");
	printArrayOfDP(dp, target + 1);
	return dp[target];
}

int main()
{
	int nums[100] = {0}, numsSize = 0, target;
	FILE *pfile = NULL;
	if ((pfile = fopen("377.txt", "r")) == NULL)
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

		fscanf(pfile, "%d", &nums[numsSize]);
		printf("%d", nums[numsSize]);
		numsSize++;
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
	fscanf(pfile, " %d", &target);
	printf(" %d ", target);
	puts("");

	printf("nums = ");
	printArray(nums, numsSize);
	printf("target = %d\n", target);

	printf("numbers of combination methods = %d\n", combinationSum4(nums, numsSize, target));

	return 0;
}