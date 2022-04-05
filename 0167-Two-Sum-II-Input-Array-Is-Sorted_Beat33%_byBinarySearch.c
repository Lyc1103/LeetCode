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

int binarySearch(int *nums, int f, int r, int t)
{
	int mid;
	while (f <= r)
	{
		mid = (f + r) / 2;
		if (nums[mid] == t)
			return mid;
		if (nums[mid] < t)
			f = mid + 1;
		else
			r = mid - 1;
	}
	return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize)
{
	int i, pos;
	int *res = (int *)malloc(2 * sizeof(int));
	*returnSize = 2;
	for (i = 0; i < numbersSize - 1; i++)
	{
		pos = binarySearch(numbers, i + 1, numbersSize - 1, target - numbers[i]);
		if (pos != -1)
		{
			res[0] = i + 1;
			res[1] = pos + 1;
			break;
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