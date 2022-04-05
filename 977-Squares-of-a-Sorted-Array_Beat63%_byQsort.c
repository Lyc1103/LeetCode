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

int cmpFunction(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *nums, int numsSize, int *returnSize)
{
	int *res = (int *)malloc(numsSize * sizeof(int));
	*returnSize = numsSize;
	for (int i = 0; i < numsSize; i++)
		res[i] = nums[i] * nums[i];
	qsort(res, *returnSize, sizeof(int), cmpFunction);
	return res;
}

int main()
{
	int nums[100] = {0}, numsSize = 0, amount;
	FILE *pfile = NULL;
	if ((pfile = fopen("977.txt", "r")) == NULL)
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
	puts("");
	printf("nums = ");
	printArray(nums, numsSize);

	int returnSize;
	int *res = sortedSquares(nums, numsSize, &returnSize);
	printf("res = ");
	printArray(res, returnSize);

	return 0;
}