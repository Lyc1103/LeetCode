#include <stdio.h>

int removeDuplicates(int *nums, int numsSize)
{
	int len = 0, last = numsSize;
	for (int i = 1; i < numsSize; i++)
	{
		// printf("nums[%d] = %d, nums[%d-1] = %d\n", i, nums[i], i, nums[i - 1]);
		if (nums[i] != nums[len])
		{
			len++;
			int tmp = nums[len];
			nums[len] = nums[i];
			nums[i] = tmp;
		}
	}
	// printf("++cur = %d\n", len + 1);
	return ++len;
}

int main()
{
	int nums[10] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
	int numsSize = 10;
	int len = removeDuplicates(nums, numsSize);

	printf("[");
	for (int i = 0; i < numsSize; i++)
	{
		if (i < len)
			printf("%d", nums[i]);
		else
			printf("_");
		printf(",");
	}
	printf("]\n");
	return 0;
}