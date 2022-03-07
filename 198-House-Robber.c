#include <stdio.h>
#include <stdint.h>

int rob(int *nums, int numsSize)
{
	if (numsSize == 1)
		return nums[0];
	if (numsSize == 2)
		return nums[0] > nums[1] ? nums[0] : nums[1];
	int16_t pre_2 = nums[0], pre_1 = nums[1], pre_0 = (pre_2 + nums[2]) > pre_1 ? (pre_2 + nums[2]) : pre_1;
	if (numsSize == 3)
		return pre_0;
	// printf("i = 2, pre_0 = %d, pre_1 = %d, pre_2 = %d\n", pre_0, pre_1, pre_2);

	int16_t tmp;
	for (int8_t i = 3; i < numsSize; i++)
	{
		tmp = pre_0;
		pre_0 = nums[i] + (pre_1 > pre_2 ? pre_1 : pre_2);
		pre_2 = pre_1;
		pre_1 = tmp;
		pre_0 = pre_0 > pre_1 ? pre_0 : pre_1;
		// printf("i = %d, pre_0 = %d, pre_1 = %d, pre_2 = %d\n", i, pre_0, pre_1, pre_2);
	}
	return pre_0;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("198.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	int res = rob(nums, numsSize);
	printf("max-val = %d\n", res);
}