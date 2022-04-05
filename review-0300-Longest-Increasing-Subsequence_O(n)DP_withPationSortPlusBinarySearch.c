// Reference: https://segmentfault.com/a/1190000003819886
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

int binarySearch(int *tails, int min, int max, int target)
{
	int mid;
	while (min <= max)
	{
		mid = (min + max) / 2;
		if (tails[mid] == target)
			return mid;
		else if (tails[mid] < target)
			min = mid + 1;
		else
			max = mid - 1;
	}
	return min;
}

int lengthOfLIS(int *nums, int numsSize)
{
	int i, tmp_pos;
	int max_len = 0;
	// tails[i] 紀錄長度為 i 之序列最末位數值
	int *tails = (int *)calloc(numsSize, sizeof(int));
	tails[0] = nums[0];

	for (i = 1; i < numsSize; i++)
	{
		printf("nums[%2d] = %2d, ", i, nums[i]);
		if (nums[i] <= tails[0])
		{
			tails[0] = nums[i];
			printf("case1 : tails[0] = %d\n", nums[i]);
		}
		else if (nums[i] > tails[max_len])
		{
			tails[++max_len] = nums[i];
			printf("case2 : tails[%d] = %d\n", max_len, tails[max_len]);
		}
		else
		{
			tmp_pos = binarySearch(tails, 0, max_len, nums[i]);
			tails[tmp_pos] = nums[i];
			printf("case3 : tails[%d] = %d\n", tmp_pos, tails[tmp_pos]);
		}
	}
	printf("tails = ");
	printArray(tails, max_len + 1);
	return max_len + 1;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("300.txt", "r")) == NULL)
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

	printf("lengthOfLIS = %d\n", lengthOfLIS(nums, numsSize));

	return 0;
}