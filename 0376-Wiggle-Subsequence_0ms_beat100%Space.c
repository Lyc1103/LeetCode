// Reference: https://segmentfault.com/a/1190000003819886
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

int wiggleMaxLength(int *nums, int numsSize)
{
	// pre_diff represents the last sign of difference before current number, 0: negative, 1:positive
	_Bool pre_diff_is_positive;
	int res_len = 1;
	int i, tmp;
	for (i = 1; i < numsSize; i++)
		if (nums[i] - nums[i - 1] != 0)
		{
			printf("nums[%d] = %d\n", i, nums[i]);
			pre_diff_is_positive = nums[i] - nums[i - 1] > 0 ? 1 : 0;
			printf("pre_diff_is_positive  = %d\n", pre_diff_is_positive);
			i++;
			res_len++;
			break;
		}
	for (; i < numsSize; i++)
	{
		printf("nums[%d] = %d\n", i, nums[i]);
		if ((tmp = nums[i] - nums[i - 1]) == 0)
			continue;
		else if (pre_diff_is_positive && tmp < 0)
		{
			printf("pre_diff_is_positive  = %d, cur_diff = %d, ", pre_diff_is_positive, tmp);
			pre_diff_is_positive = 0;
			res_len++;
			printf("len = %d\n", res_len);
		}
		else if (!pre_diff_is_positive && tmp > 0)
		{
			printf("pre_diff_is_positive  = %d, cur_diff = %d, ", pre_diff_is_positive, tmp);
			pre_diff_is_positive = 1;
			res_len++;
			printf("len = %d\n", res_len);
		}
	}
	return res_len;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("376.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}
	printf("input: ");
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{

		fscanf(pfile, "%d", &nums[numsSize]);
		printf("%d", nums[numsSize]);
		numsSize++;
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");
	printf("nums = ");
	printArray(nums, numsSize);

	printf("wiggleMaxLength = %d\n", wiggleMaxLength(nums, numsSize));

	return 0;
}