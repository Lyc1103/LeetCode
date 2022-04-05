#include <stdio.h>

int singleNumber(int *nums, int numsSize)
{
	int i, res = nums[0];
	for (i = 1; i < numsSize; i++)
		res ^= nums[i];
	return res;
}

int main()
{
	int numsSize = 5;
	int nums[5] = {4, 1, 2, 1, 2};
	int single = singleNumber(nums, numsSize);
	printf("single num = %d\n", single);

	return 0;
}