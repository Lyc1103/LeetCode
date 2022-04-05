#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findPeakElement(int *nums, int numsSize)
{
	if (numsSize == 1)
		return 0;
	if (nums[0] > nums[1])
		return 0;
	if (nums[numsSize - 1] > nums[numsSize - 2])
		return numsSize - 1;
	for (int front = 1, rear = numsSize - 2, mid; front <= rear;)
	{
		mid = (front + rear) / 2;
		if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
			return mid;
		else if (nums[mid] > nums[mid - 1])
			front = mid + 1;
		else
			rear = mid - 1;
	}
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
	puts("");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("162.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[50] = {0}, numsSize = 0, target;
	dealWithInputFile_ForNums(pfile, nums, &numsSize);

	printf("nums = ");
	printArray_int(nums, numsSize);

	printf("peak index = %d\n", findPeakElement(nums, numsSize));

	return 0;
}
