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

typedef struct
{
	int *data;
	int *pos;
	int rear;
} Bucket;

void radixSort(int *nums, int numsSize)
{
	Bucket *buck = (Bucket *)malloc(10 * sizeof(Bucket));
	for (int i = 0; i < 10; i++)
	{
		buck[i].data = (int *)calloc(500, sizeof(int));
		buck[i].rear = 0;
	}

	int div = 1;
	for (int n = 0; n < 4; n++)
	{
		for (int i = 0; i < 10; i++)
			buck[i].rear = 0;

		for (int i = 0; i < numsSize; i++)
		{
			int position = (nums[i] / div) % 10;
			buck[position].data[buck[position].rear] = nums[i];
			(buck[position].rear)++;
		}
		div *= 10;

		// puts("");
		// printf("nums: ");
		// printArray(nums, numsSize);
		int cnt = 0, flag = 1;
		for (int i = 0; i < 10; i++)
		{
			// printf("buck[%d]: ", i);
			// printArray(buck[i].data, buck[i].rear);

			for (int j = 0; j < buck[i].rear; j++)
			{
				nums[cnt] = buck[i].data[j];
				if (nums[cnt] * 10 / div != 0)
					flag = 0;
				// printf("nums[cnt = %d] = buck[i = %d].data[j = %d] = %d\n", cnt, i, j, nums[cnt]);
				cnt++;
			}
		}
		if (flag)
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		free(buck[i].data);
	}
	free(buck);

	return;
}

int maxProduct(int *nums, int numsSize)
{
	// printArray(nums, numsSize);
	radixSort(nums, numsSize);
	// printArray(nums, numsSize);
	return (nums[numsSize - 1] - 1) * (nums[numsSize - 2] - 1);
}

int main()
{
	int nums[4] = {1000, 4, 5, 1000};
	int numsSize = 4;
	int res = maxProduct(nums, numsSize);
	printf("maxProduct = %d\n", res);

	return 0;
}