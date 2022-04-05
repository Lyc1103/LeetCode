#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int findMin(int *nums, int numsSize)
{
	int front = 0, rear = numsSize - 1, mid;
	while (front <= rear)
	{
		mid = (front + rear) / 2;
		if (mid + 1 >= numsSize)
			return nums[mid];
		if (nums[mid] > nums[mid + 1])
			return nums[mid + 1];
		if (nums[front] < nums[mid] && nums[mid] > nums[rear])
			front = mid;
		else if (nums[front] > nums[mid] && nums[mid] < nums[rear])
			rear = mid;
		else
			return nums[0];
	}
	return nums[0];
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
	if ((pfile = fopen("153.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[50] = {0}, numsSize = 0, target;
	dealWithInputFile_ForNums(pfile, nums, &numsSize);

	printf("nums = ");
	printArray_int(nums, numsSize);

	printf("min = %d\n", findMin(nums, numsSize));

	return 0;
}
