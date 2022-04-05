// Reference: https://leetcode.com/problems/subarray-product-less-than-k/discuss/1884230/python3-sliding-window-solution-with-explanation-why-right-left-%2B-1
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// Note: for array of length n, you can have n contiguous subarray contain the last element
// here is indices of subarray it can have
// [n-1]
// [n-1, n-2]
// [n-1, n-2, n-3]
// [n-1, n-2, n-3, n-4]
// [n-1, n-2, n-3, n-4, n-5]
// ...
// we can keep adding previous elements to generate a new contiguous subarray
// so once we have add a new element to current array
// we can have n + 1 new contiguous subarray where n + 1 is the length of new array

// [1, 2, 3] k = 10, res = 6
// [1], new combinations [1]
// [1, 2], new combinations = [2], [2, 1]
// [1, 2, 3], new combinations = [3], [3, 2], [3, 2, 1]
int numSubarrayProductLessThanK(int *nums, int numsSize, int k)
{
	if (k < 1)
		return 0;
	int product = 1, res = 0;
	// sliding window
	for (int front = 0, rear = 0; rear < numsSize; rear++)
	{
		if (nums[rear] >= k)
		{
			front = rear + 1;
			product = 1;
		}
		else
		{
			product *= nums[rear];
			while (product >= k && front <= rear)
				product /= nums[front++];
			res += rear - front + 1;
		}
	}
	return res;
}

int *dealWithInputFile_ForNums(FILE *pfile, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	*numsSize = 0;
	int *nums = (int *)malloc(50 * sizeof(int));
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
	return nums;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("713.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	printf("input: ");
	int numsSize, k;
	int *nums = dealWithInputFile_ForNums(pfile, &numsSize);
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &k);
	printf(" %d\n", k);

	printf("res = %d\n", numSubarrayProductLessThanK(nums, numsSize, k));

	return 0;
}