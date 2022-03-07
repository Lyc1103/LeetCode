#include <stdio.h>

int singleNumber(int *nums, int numsSize)
{
	int res = 0;
	for (int i = 0; i < numsSize; i++)
	{
		res ^= nums[i];
	}
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