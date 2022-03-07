#include <stdio.h>

void printArray(int *nums, int numsSize, int len)
{
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
	return;
}

int removeElement(int *nums, int numsSize, int val)
{
	int len = 0, last = numsSize;
	while (len < last)
	{
		if (nums[len] == val)
		{
			int tmp = nums[--last];
			nums[last] = nums[len];
			nums[len] = tmp;
		}
		else
			len++;
	}
	return len;
}

int main()
{
	int nums[8] = {0, 1, 2, 2, 3, 0, 4, 2};
	int numsSize = 8;
	int del_val = 2;
	printArray(nums, numsSize, numsSize);
	int len = removeElement(nums, numsSize, del_val);
	printArray(nums, numsSize, len);

	return 0;
}