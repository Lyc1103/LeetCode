#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int recursiveFindMin(int *nums, int numsSize, int left, int right)
{
	if (right < left)
		return 0;
	if (right == left)
		return (right + 1) % numsSize;

	int mid = left + (right - left) / 2;
	if (mid < right && nums[mid] > nums[mid + 1])
		return mid + 1;
	if (mid > left && nums[mid] < nums[mid - 1])
		return mid;

	if (nums[mid] <= nums[left])
		return recursiveFindMin(nums, numsSize, left, mid - 1);
	else
		return recursiveFindMin(nums, numsSize, mid + 1, right);
}

int findMin(int *nums, int numsSize)
{
	if (numsSize == 1)
		return nums[0];
	return nums[recursiveFindMin(nums, numsSize, 0, numsSize - 1)];
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
