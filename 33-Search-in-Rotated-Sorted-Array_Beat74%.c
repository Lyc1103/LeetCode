#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int binarySearch(int *nums, int front, int rear, int target)
{
	int mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (nums[mid] == target)
			return mid;
		if (nums[mid] < target)
			front = mid + 1;
		else
			rear = mid - 1;
	}
	return -1;
}

int findPivot(int *nums, int numsSize)
{
	int front = 0, rear = numsSize - 1, mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (mid + 1 > numsSize || nums[mid] > nums[mid + 1])
			return mid + 1;
		if (nums[front] < nums[mid] && nums[mid] > nums[rear])
			front = mid;
		else if (nums[front] > nums[mid] && nums[mid] < nums[rear])
			rear = mid;
		else
			return 0;
	}
	return 0;
}

int search(int *nums, int numsSize, int target)
{
	if (numsSize == 1)
		return nums[0] == target ? 0 : -1;
	int pivot = findPivot(nums, numsSize);
	// printf("pivot = %d\n", pivot);

	if (pivot == 0)
		return binarySearch(nums, 0, numsSize - 1, target);
	else if (target == nums[0])
		return 0;
	else if (target > nums[0])
		return binarySearch(nums, 0, pivot - 1, target);
	else
		return binarySearch(nums, pivot, numsSize - 1, target);
	return -1;
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
	if ((pfile = fopen("33.txt", "r")) == NULL)
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
	printf("target = %d\n", target);

	printf("res = %d\n", search(nums, numsSize, target));

	return 0;
}
