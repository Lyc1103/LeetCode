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

int getMaxLen(int *nums, int numsSize)
{
	int res_len = 0;
	int pos_len = 0;
	int neg_len = 0;
	int tmp;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] > 0)
		{
			pos_len++;
			if (neg_len)
				neg_len++;
		}
		else if (nums[i] < 0)
		{
			tmp = pos_len;
			if (neg_len)
				pos_len = neg_len + 1;
			else
				pos_len = 0;
			neg_len = tmp + 1;
		}
		else // nums[i] == 0
		{
			pos_len = 0;
			neg_len = 0;
		}

		res_len = res_len > pos_len ? res_len : pos_len;
	}
	return res_len;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("1567.txt", "r")) == NULL)
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

	int max_len = getMaxLen(nums, numsSize);
	printf("max_len = %d\n", max_len);

	return 0;
}