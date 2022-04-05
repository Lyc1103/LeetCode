#include <stdio.h>
#include <stdint.h>

int rob(int *nums, int numsSize)
{
	if (numsSize == 1)
		return nums[0];
	if (numsSize == 2)
		return nums[0] > nums[1] ? nums[0] : nums[1];
	int16_t pre_1 = nums[0];
	int16_t pre_0 = nums[0] > nums[1] ? nums[0] : nums[1];
	if (numsSize == 3)
	{
		if (pre_0 > nums[2])
			return pre_0;
		else
			return nums[2];
	}
	printf("i = 1, pre_0 = %d, pre_1 = %d\n", pre_0, pre_1);

	int16_t tmp;
	for (int8_t i = 2; i < numsSize - 1; i++)
	{
		tmp = pre_0;
		if (pre_1 + nums[i] > pre_0)
		{
			pre_0 = pre_1 + nums[i];
		}
		pre_1 = tmp;
		printf("i = %d, pre_0 = %d, pre_1 = %d\n", i, pre_0, pre_1);
	}

	int16_t _pre_1 = nums[1];
	int16_t _pre_0 = nums[1] > nums[2] ? nums[1] : nums[2];
	printf("i = 2, _pre_0 = %d, _pre_1 = %d\n", _pre_0, _pre_1);
	for (int8_t i = 3; i < numsSize; i++)
	{
		tmp = _pre_0;
		if (_pre_1 + nums[i] > _pre_0)
			_pre_0 = _pre_1 + nums[i];
		_pre_1 = tmp;
		printf("i = %d, _pre_0 = %d, _pre_1 = %d\n", i, _pre_0, _pre_1);
	}

	return _pre_0 > pre_0 ? _pre_0 : pre_0;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("213.txt", "r")) == NULL)
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