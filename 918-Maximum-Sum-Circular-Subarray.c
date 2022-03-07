#include <stdio.h>
#include <stdlib.h>

int maxSubarraySumCircular(int *nums, int numsSize)
{
	if (numsSize == 1)
		return nums[0];
	int i, dp_cur_max = nums[0], dp_cur_min = nums[0];
	int sum = nums[0], max_sum = nums[0], min_sum = nums[0];
	for (i = 1; i < numsSize; i++)
	{
		dp_cur_max = dp_cur_max + nums[i] > nums[i] ? dp_cur_max + nums[i] : nums[i];
		max_sum = dp_cur_max > max_sum ? dp_cur_max : max_sum;
		printf("nums[%d] = %2d, dp_%2d = %2d, max_sum = %d\n", i, nums[i], i, dp_cur_max, max_sum);
		sum += nums[i];
		dp_cur_min = dp_cur_min + nums[i] < nums[i] ? dp_cur_min + nums[i] : nums[i];
		min_sum = dp_cur_min < min_sum ? dp_cur_min : min_sum;
		printf("nums[%d] = %2d, dp_%2d = %2d, min_sum = %d\n", i, nums[i], i, dp_cur_min, min_sum);
	}

	printf("max(max_sum, sum-min_sum) = %d\n", max_sum > sum - min_sum ? max_sum : sum - min_sum);
	if (max_sum <= 0)
		return max_sum;
	return max_sum > sum - min_sum ? max_sum : sum - min_sum;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("918.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	int max_sum = maxSubarraySumCircular(nums, numsSize);
	printf("maximum-sum = %d\n", max_sum);

	return 0;
}