#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target)
{
	int start = 0, end = numsSize - 1;
	while (start < end)
	{
		int pos = (start + end) / 2;
		if (nums[pos] == target)
			return pos;
		else if (nums[pos] > target)
		{
			end = pos - 1;
		}
		else
		{
			start = pos + 1;
		}
	}
	if (nums[start] < target)
		return start + 1;
	else
		return start;
}

int main()
{
	int nums[4] = {1, 3, 5, 6};
	int numsSize = 4;
	int target = 5;
	int pos = searchInsert(nums, numsSize, target);
	printf("%d\n", pos);
}