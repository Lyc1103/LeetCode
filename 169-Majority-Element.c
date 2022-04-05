#include <stdio.h>
#include <stdint.h>

int majorityElement(int *nums, int numsSize)
{
	// Boyer-Moore majority vote algorthm
	int max_cnt = 1, max_num = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		if (max_num == nums[i])
		{
			max_cnt++;
		}
		else
		{
			max_cnt--;
			if (max_cnt == 0)
			{
				max_cnt = 1;
				max_num = nums[i];
			}
		}
	}
	return max_num;
}

int partition(int *nums, int s, int t)
{
	int pivot_v = nums[s];
	int i = s - 1, j = t + 1;
	for (int k = s; k <= t; k++)
	{
		if (nums[k] < pivot_v)
		{
			i++;
			int tmp = nums[i];
			nums[i] = nums[k];
			nums[k] = tmp;
		}
		else if (nums[k] > pivot_v)
		{
			j--;
			int tmp = nums[j];
			nums[j] = nums[k];
			nums[k] = tmp;
		}
	}
	i++;
	return i;
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

int main()
{
	int nums[1] = {100};
	int numsSize = 1;
	int max_num = majorityElement(&nums, numsSize);
	quicksort(nums, 0, numsSize - 1);
	printf("sorted list = {");
	for (int i = 0; i < numsSize - 1; i++)
		printf(" %d,", nums[i]);
	printf(" %d }\n", nums[numsSize - 1]);
	printf("majorityElement = %d\n", max_num);
	return 0;
}