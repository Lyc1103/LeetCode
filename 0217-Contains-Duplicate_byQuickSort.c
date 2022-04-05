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

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *nums, int s, int t)
{
	int tmp, half = (s + t) / 2;
	int cmp1 = nums[s], cmp2 = nums[half], cmp3 = nums[t];
	int pivot_v = cmp3;
	if (cmp1 > cmp2 && cmp2 > cmp3)
	{
		pivot_v = cmp2;
		// tmp = nums[half];
		// nums[half] = nums[t];
		// nums[t] = tmp;
		swap(&nums[half], &nums[t]);
	}
	else if (cmp2 > cmp1 && cmp1 > cmp3)
	{
		pivot_v = cmp1;
		// tmp = nums[s];
		// nums[s] = nums[t];
		// nums[t] = tmp;
		swap(&nums[s], &nums[t]);
	}
	else if (cmp3 > cmp1 && cmp1 > cmp2)
	{
		pivot_v = cmp1;
		// tmp = nums[s];
		// nums[s] = nums[t];
		// nums[t] = tmp;
		swap(&nums[s], &nums[t]);
	}
	else if (cmp3 > cmp2 && cmp2 > cmp1)
	{
		pivot_v = cmp2;
		// tmp = nums[half];
		// nums[half] = nums[t];
		// nums[t] = tmp;
		swap(&nums[half], &nums[t]);
	}

	int i = s - 1;
	for (int j = s; j < t; j++)
	{
		if (nums[j] < pivot_v)
		{
			i++;
			swap(&nums[i], &nums[j]);
		}
	}
	swap(&nums[i + 1], &nums[t]);

	return i + 1;
}

void quicksort(int *nums, int s, int t)
{
	if (s < t)
	{
		int pivot = partition(nums, s, t);
		quicksort(nums, s, pivot - 1);
		quicksort(nums, pivot + 1, t);
	}
	return;
}

_Bool containsDuplicate(int *nums, int numsSize)
{
	if (numsSize <= 1)
		return 0;
	quicksort(nums, 0, numsSize - 1);
	for (int i = 1; i < numsSize; i++)
	{
		if (nums[i] == nums[i - 1])
			return 1;
	}
	return 0;
}

int main()
{
	int nums[4] = {1, 2, 3, 1};
	int numsSize = 4;
	printArray(nums, numsSize);
	_Bool flag = containsDuplicate(nums, numsSize);
	printArray(nums, numsSize);
	if (flag)
		puts("true");
	else
		puts("flase");

	return 0;
}