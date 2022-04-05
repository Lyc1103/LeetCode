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

void radixSort(int *nums, int numsSize, int *buffer)
{
	Bucket *buck = (Bucket *)malloc(10 * sizeof(Bucket));
	Bucket *neg_buck = (Bucket *)malloc(10 * sizeof(Bucket));
	for (int i = 0; i < 10; i++)
	{
		buck[i].data = (int *)calloc(20000, sizeof(int));
		buck[i].pos = (int *)calloc(20000, sizeof(int));
		buck[i].rear = 0;
		neg_buck[i].data = (int *)calloc(20000, sizeof(int));
		neg_buck[i].pos = (int *)calloc(20000, sizeof(int));
		neg_buck[i].rear = 0;
	}

	int div = 1;
	for (int n = 0; n < 9; n++)
	{
		for (int i = 0; i < 10; i++)
		{
			buck[i].rear = 0;
			neg_buck[i].rear = 0;
		}

		for (int i = 0; i < numsSize; i++)
		{
			int position;
			if (nums[i] >= 0)
			{
				position = (nums[i] / div) % 10;
				buck[position].data[buck[position].rear] = nums[i];
				buck[position].pos[buck[position].rear] = buffer[i];
				(buck[position].rear)++;
			}
			else
			{
				if (div > 1)
					position = -(nums[i] / div) % 10;
				else
					position = ((-(nums[i] + 1) / div) % 10 + 1) % 10;
				// printf("nums = %d, position = %d\n", nums[i], position);
				neg_buck[position].data[neg_buck[position].rear] = nums[i];
				neg_buck[position].pos[neg_buck[position].rear] = buffer[i];
				(neg_buck[position].rear)++;
			}
		}
		// puts("");
		div *= 10;
		// printf("nums: ");
		// printArray(nums, numsSize);
		// printf("buffer: ");
		// printArray(buffer, numsSize);
		int cnt = 0, flag = 1;
		for (int i = 9; i >= 0; i--)
		{
			// printf("buck[%d]: ", i);
			// printArray(buck[i].pos, buck[i].rear);
			// printf("neg_buck[%d]: ", i);
			// printArray(neg_buck[i].pos, neg_buck[i].rear);
			if (i > 0 && neg_buck[i].rear)
				flag = 0;

			for (int j = 0; j < neg_buck[i].rear; j++)
			{
				nums[cnt] = neg_buck[i].data[j];
				// printf("nums[cnt = %d] = buck[i = %d].data[j = %d] = %d\n", cnt, i, j, nums[cnt]);
				buffer[cnt] = neg_buck[i].pos[j];
				cnt++;
			}
		}
		for (int i = 0; i < 10; i++)
		{
			// printf("buck[%d]: ", i);
			// printArray(buck[i].pos, buck[i].rear);
			// printf("neg_buck[%d]: ", i);
			// printArray(neg_buck[i].pos, neg_buck[i].rear);
			if (i > 0 && buck[i].rear)
				flag = 0;

			for (int j = 0; j < buck[i].rear; j++)
			{
				nums[cnt] = buck[i].data[j];
				// printf("nums[cnt = %d] = buck[i = %d].data[j = %d] = %d\n", cnt, i, j, nums[cnt]);
				buffer[cnt] = buck[i].pos[j];
				cnt++;
			}
		}
		if (flag)
			break;
	}
	for (int i = 0; i < 10; i++)
	{
		free(buck[i].data);
		free(buck[i].pos);
		free(neg_buck[i].data);
		free(neg_buck[i].pos);
	}
	free(buck);
	free(neg_buck);
	return;
}

_Bool containsNearbyAlmostDuplicate(int *nums, int numsSize, int k, int t)
{
	if (numsSize <= 1)
		return 0;
	int *buffer = (int *)calloc(numsSize, sizeof(int));
	for (int i = 0; i < numsSize; i++)
	{
		buffer[i] = i;
	}

	// printArray(nums, numsSize);
	// printArray(buffer, numsSize);
	radixSort(nums, numsSize, buffer);
	// printArray(nums, numsSize);
	// printArray(buffer, numsSize);

	int64_t cmp_num;
	int cmp_pos, i = 0, j = 1;
	while (i < numsSize && j < numsSize)
	{
		cmp_pos = buffer[i] > buffer[j] ? (buffer[i] - buffer[j]) : (buffer[j] - buffer[i]);
		cmp_num = (int64_t)nums[j] - (int64_t)nums[i];
		if (cmp_num <= t && cmp_pos <= k)
		{
			// printf("nums[%d] = %d, nums[%d] = %d, buffer[%d] = %d, buffer[%d] = %d\n", i, nums[i], j, nums[j], i, buffer[i], j, buffer[j]);
			// printf("cmp_pos = %d, cmp_num = %d\n", cmp_pos, cmp_num);
			return 1;
		}
		else if (cmp_num > t)
		{
			i++;
			j = i + 1;
		}
		else
		{
			j++;
		}
	}

	free(buffer);
	return 0;
}

int main()
{
	int nums[6] = {-2147483648, 1, 2, 3, 4, 5};
	int numsSize = 6;
	int k = 2, t = 3;
	// printArray(nums, numsSize);
	_Bool flag = containsNearbyAlmostDuplicate(nums, numsSize, k, t);
	// printArray(nums, numsSize);

	if (flag)
		puts("true");
	else
		puts("flase");

	return 0;
}