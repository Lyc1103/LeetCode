#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

int jump(int *nums, int numsSize)
{
	if (numsSize == 1)
		return 0;
	if (numsSize == 2)
	{
		if (nums[0] > 0)
			return 1;
		else
			return 0;
	}
	int16_t *dp_min_steps = (int16_t *)calloc(numsSize, sizeof(int16_t));

	int16_t i, pos = (int16_t)numsSize - 2, min_step = 0;
	int16_t tmp;
	while (pos >= 0)
	{

		printf("pos = %d, nums[%d] = %d\n", pos, pos, nums[pos]);
		if (pos + nums[pos] >= numsSize - 1)
		{
			dp_min_steps[pos] = 1;
			printf("dp_min_steps[%d] = %d\n\n", pos, 1);
			pos--;
			continue;
		}

		min_step = 10001;
		for (i = pos + 1; i <= pos + nums[pos] && i <= numsSize - 1; i++)
		{
			printf("// i = %d, nums[%d] = %d, dp_min_steps[%d] = %d\n", i, i, nums[i], i, dp_min_steps[i]);
			min_step = min_step < (dp_min_steps[i] + 1) ? min_step : (dp_min_steps[i] + 1);
		}
		printf("dp_min_steps[%d] = %d\n\n", pos, min_step);
		dp_min_steps[pos] = min_step;
		pos--;
	}
	printArray(dp_min_steps, numsSize);

	return dp_min_steps[0];
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("45.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	int min_step = jump(nums, numsSize);
	printf("min_step = %d\n", min_step);

	return 0;
}