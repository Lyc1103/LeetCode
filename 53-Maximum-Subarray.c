#include <stdio.h>
#include <stdlib.h>

int maxSubArray(int *nums, int numsSize)
{
	if (numsSize == 1)
		return nums[0];
	int dp_cur = nums[0];
	int max_sum = nums[0];
	for (int i = 1; i < numsSize; i++)
	{
		dp_cur = dp_cur + nums[i] > nums[i] ? dp_cur + nums[i] : nums[i];
		max_sum = dp_cur > max_sum ? dp_cur : max_sum;
		// printf("nums[%d] = %2d, dp_%2d = %2d, max_sum = %d\n", i, nums[i], i, dp_cur, max_sum);
	}
	return max_sum;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("53.txt", "r")) == NULL)
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

	int max_sum = maxSubArray(nums, numsSize);
	printf("maximum-sum = %d\n", max_sum);

	return 0;
}