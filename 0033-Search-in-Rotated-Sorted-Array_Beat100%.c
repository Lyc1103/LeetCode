// Reference: https://hackmd.io/@kenjin/rJwzA6gyB
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

/* Standard Binary Search function*/
int binarySearch(int *nums, int left, int right, int target)
{
	if (right < left)
		return -1;

	int mid = left + (right - left) / 2;
	if (target == nums[mid])
		return mid;
	if (target > nums[mid])
		return binarySearch(nums, mid + 1, right, target);
	else
		return binarySearch(nums, left, mid - 1, target);
}

/*
 *  - Find the pivot that is the index of the max num in array.
 *  - "return -1" means that we didn't find pivot index
 */
int findPivot(int *nums, int left, int right)
{
	if (right < left)
		return -1;
	if (right == left)
		return right;

	int mid = left + (right - left) / 2;
	if (mid < right && nums[mid] > nums[mid + 1])
		return mid;
	if (mid > left && nums[mid] < nums[mid - 1])
		return (mid - 1);

	if (nums[mid] <= nums[left])
		return findPivot(nums, left, mid - 1);
	else
		return findPivot(nums, mid + 1, right);
}

int search(int *nums, int numsSize, int target)
{
	int rotatedPivot = findPivot(nums, 0, numsSize - 1);

	// This case is that the array was not rotated at all
	if (rotatedPivot == -1)
		return binarySearch(nums, 0, numsSize - 1, target);

	if (target == nums[rotatedPivot])
		return rotatedPivot;
	if (nums[0] <= target)
		return binarySearch(nums, 0, rotatedPivot - 1, target);
	else
		return binarySearch(nums, rotatedPivot + 1, numsSize - 1, target);
	return 0;
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
