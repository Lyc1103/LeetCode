#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize)
{
	int i, cur_pos;
	int *res = (int *)malloc(2 * sizeof(int));
	int buffer[4001] = {0};
	*returnSize = 2;
	for (i = 0; i < numbersSize; i++)
	{
		cur_pos = numbers[i] + 2000;
		if (buffer[cur_pos] != 0)
		{
			res[0] = buffer[cur_pos];
			res[1] = i + 1;
			break;
		}
		else
		{
			buffer[target - numbers[i] + 2000] = i + 1;
		}
	}
	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("167.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int target;
	int nums[100] = {0}, numsSize = 0;
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &(nums[numsSize]));
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
	printf(" %d", target);
	puts("");

	printf("nums = ");
	printArray(nums, numsSize);
	printf("target = %d\n", target);

	int returnSize;
	int *res = twoSum(nums, numsSize, target, &returnSize);
	printf("res = ");
	printArray(res, returnSize);
	printf("i.e. two sum of %d = nums[%d] + nums[%d] = %d + %d\n", target, res[0] - 1, res[1] - 1, nums[res[0] - 1], nums[res[1] - 1]);

	free(res);
	return 0;
}