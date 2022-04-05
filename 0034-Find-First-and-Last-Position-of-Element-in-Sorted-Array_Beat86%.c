#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int binarySearchHead(int *nums, int front, int rear, int target)
{
	int mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (nums[mid] == target && (mid - 1 < 0 || nums[mid - 1] != target))
			return mid;
		else if (nums[mid] >= target)
			rear = mid - 1;
		else
			front = mid + 1;
	}
	return -1;
}

int binarySearchTail(int *nums, int numsSize, int front, int rear, int target)
{
	int mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (nums[mid] == target && (mid + 1 > numsSize - 1 || nums[mid + 1] != target))
			return mid;
		else if (nums[mid] > target)
			rear = mid - 1;
		else
			front = mid + 1;
	}
	return -1;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *searchRange(int *nums, int numsSize, int target, int *returnSize)
{
	*returnSize = 2;
	int *ret = (int *)malloc(2 * sizeof(int));
	if (numsSize == 0)
	{
		ret[0] = ret[1] = -1;
		return ret;
	}
	ret[0] = binarySearchHead(nums, 0, numsSize - 1, target);
	if (ret[0] == -1)
		ret[1] = -1;
	else
		ret[1] = binarySearchTail(nums, numsSize, 0, numsSize - 1, target);
	return ret;
}

void printArray_int(int *nums, int numsSize)
{
	if (numsSize == 0)
	{
		puts("[]");
		return;
	}
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%d,", nums[i]);
	}
	printf("%d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

void dealWithInputFile_ForNums(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			if (flag)
			{
				nums[*numsSize] = sum;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum;
			(*numsSize)++;
			sum = 0;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("34.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[50] = {0}, numsSize = 0, target;
	dealWithInputFile_ForNums(pfile, nums, &numsSize);
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &target);
	printf(" %d\n", target);

	printf("nums = ");
	printArray_int(nums, numsSize);

	int returnSize;
	int *ret = searchRange(nums, numsSize, target, &returnSize);
	printf("ret:");
	printArray_int(ret, returnSize);

	return 0;
}
