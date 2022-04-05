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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *nums, int numsSize, int *returnSize)
{
	int *res = (int *)malloc(numsSize * sizeof(int));
	*returnSize = numsSize;
	numsSize--;

	int front = 0;
	int rear = numsSize;
	while (numsSize >= 0)
	{
		if (nums[front] * nums[front] >= nums[rear] * nums[rear])
		{
			res[numsSize--] = nums[front] * nums[front];
			front++;
		}
		else
		{
			res[numsSize--] = nums[rear] * nums[rear];
			rear--;
		}
	}
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