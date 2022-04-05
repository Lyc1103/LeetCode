#include <stdio.h>
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
	int *res = (int *)calloc(2, sizeof(int));
	int max = nums[0], min = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		if (min > nums[i])
			min = nums[i];
		if (max < nums[i])
			max = nums[i];
	}
	int *hashtable = calloc(max - min + 1, sizeof(int));
	int offset = min;
	hashtable[nums[0] - offset] = -1;
	for (int i = 1; i < numsSize; i++)
	{
		hashtable[nums[i] - offset] = i;
	}
	// for (int i = 0; i < max - min + 1; i++)
	// {
	// 	printf("hashtable[%d](index = %d) = %d\n", i, i + offset, hashtable[i]);
	// }
	int doub_flag = 0, tmp_index;
	for (int i = 0; i < numsSize; i++)
	{
		// printf("target = %d, nums[%d] = %d\n", target, i, nums[i]);
		// printf("target - nums[%d] = %d\n", i, target-nums[i]);
		if (target - nums[i] - offset < 0 || target - nums[i] > max)
			;
		else
		{
			// printf("nums[%d] = %d -> hashtable[%d] = %d, hashtable[target-%d] = %d\n", i, nums[i], nums[i]-offset, hashtable[nums[i]-offset], target-nums[i]-offset, hashtable[target-nums[i]-offset]);
			if (hashtable[target - nums[i] - offset] > 0 && hashtable[nums[i] - offset] != hashtable[target - nums[i] - offset])
			{
				res[0] = hashtable[nums[i] - offset];
				res[1] = hashtable[target - nums[i] - offset];
				if (res[0] == -1)
					res[0] = 0;
			}
		}
		if (nums[i] * 2 == target)
		{
			if (doub_flag == 0)
			{
				tmp_index = i;
				doub_flag = 1;
			}
			else
			{
				res[0] = i;
				res[1] = tmp_index;
			}
		}
	}
	free(hashtable);
	*returnSize = 2;
	return res;
}

int main()
{
	int nums[5] = {-1, -2, -3, -4, -5};
	int numsSize = 5;
	int target = -8;
	int *index;
	index = twoSum(&nums, numsSize, target, &nums);
	printf("[%d, %d]\n", index[0], index[1]);
	return 0;
}