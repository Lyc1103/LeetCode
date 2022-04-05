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
/*
void merge(int *nums, int f, int m, int r, int *buffer)
{
	int n1 = m - f + 1;
	int n2 = r - m;
	int *nums1 = (int *)calloc(n1, sizeof(int));
	int *nums2 = (int *)calloc(n2, sizeof(int));
	int *buffer1 = (int *)calloc(n1, sizeof(int));
	int *buffer2 = (int *)calloc(n2, sizeof(int));

	for (int i = 0; i < n1; i++)
	{
		nums1[i] = nums[f + i];
		buffer1[i] = buffer[f + i];
	}
	for (int i = 0; i < n2; i++)
	{
		nums2[i] = nums[m + 1 + i];
		buffer2[i] = buffer[m + 1 + i];
	}
	// puts("before:");
	// printf("nums = ");
	// printArray(nums, 4);
	// printf("buffer1 = ");
	// printArray(buffer1, n1);
	// printf("buffer2 = ");
	// printArray(buffer2, n2);
	// printf("buffer = ");
	// printArray(buffer, 4);

	int pos1 = 0, pos2 = 0, pos = f;
	while (pos1 < n1 && pos2 < n2)
	{
		if (nums1[pos1] <= nums2[pos2])
		{
			nums[pos] = nums1[pos1];
			buffer[pos] = buffer1[pos1];
			pos++;
			pos1++;
		}
		else
		{
			nums[pos] = nums2[pos2];
			buffer[pos] = buffer2[pos2];
			pos++;
			pos2++;
		}
	}

	while (pos1 < n1)
	{
		nums[pos] = nums1[pos1];
		buffer[pos] = buffer1[pos1];
		pos++;
		pos1++;
	}

	while (pos2 < n2)
	{
		nums[pos] = nums2[pos2];
		buffer[pos] = buffer2[pos2];
		pos++;
		pos2++;
	}

	// puts("after:");
	// printf("nums = ");
	// printArray(nums, 4);
	// printf("buffer1 = ");
	// printArray(buffer1, n1);
	// printf("buffer2 = ");
	// printArray(buffer2, n2);
	// printf("buffer = ");
	// printArray(buffer, 4);
	// puts("");

	free(nums1);
	free(nums2);
	free(buffer1);
	free(buffer2);
	return;
}

void mergeSort(int *nums, int f, int r, int *buffer)
{
	if (f < r)
	{
		int m = (f + r) / 2;
		mergeSort(nums, f, m, buffer);
		mergeSort(nums, m + 1, r, buffer);
		merge(nums, f, m, r, buffer);
	}
}
*/

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
		buck[i].data = (int *)calloc(100000, sizeof(int));
		buck[i].pos = (int *)calloc(100000, sizeof(int));
		buck[i].rear = 0;
		neg_buck[i].data = (int *)calloc(100000, sizeof(int));
		neg_buck[i].pos = (int *)calloc(100000, sizeof(int));
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
				position = (-nums[i] / div) % 10;
				neg_buck[position].data[neg_buck[position].rear] = nums[i];
				neg_buck[position].pos[neg_buck[position].rear] = buffer[i];
				(neg_buck[position].rear)++;
			}
		}
		div *= 10;
		// printf("nums: ");
		// printArray(nums, numsSize);
		// printf("buffer: ");
		// printArray(buffer, numsSize);
		int cnt = 0, flag = 1;
		for (int i = 0; i < 10; i++)
		{
			// printf("buck[%d]: ", i);
			// printArray(buck[i].pos, buck[i].rear);
			// printf("neg_buck[%d]: ", i);
			// printArray(neg_buck[i].pos, neg_buck[i].rear);
			if (i > 0 && buck[i].rear && neg_buck[i].rear)
				flag = 0;

			for (int j = 0; j < buck[i].rear; j++)
			{
				nums[cnt] = buck[i].data[j];
				// printf("nums[cnt = %d] = buck[i = %d].data[j = %d] = %d\n", cnt, i, j, nums[cnt]);
				buffer[cnt] = buck[i].pos[j];
				cnt++;
			}
			for (int j = 0; j < neg_buck[i].rear; j++)
			{
				nums[cnt] = neg_buck[i].data[j];
				// printf("nums[cnt = %d] = buck[i = %d].data[j = %d] = %d\n", cnt, i, j, nums[cnt]);
				buffer[cnt] = neg_buck[i].pos[j];
				cnt++;
			}
		}
		if (flag)
			break;
	}
	return;
}

_Bool containsNearbyDuplicate(int *nums, int numsSize, int k)
{
	if (numsSize <= 1)
		return 0;
	int *buffer = (int *)calloc(numsSize, sizeof(int));
	for (int i = 0; i < numsSize; i++)
	{
		buffer[i] = i;
	}

	// mergeSort(nums, 0, numsSize - 1, buffer);
	radixSort(nums, numsSize, buffer);

	for (int i = 1; i < numsSize; i++)
	{
		int cmp = buffer[i] > buffer[i - 1] ? (buffer[i] - buffer[i - 1]) : (buffer[i - 1] - buffer[i]);
		if (nums[i] == nums[i - 1] && cmp <= k)
		{
			// printf("nums[%d] = %d, nums[%d] = %d, buffer[%d] = %d, buffer[%d] = %d\n", i, nums[i], i - 1, nums[i - 1], i, buffer[i], i - 1, buffer[i - 1]);
			return 1;
		}
	}
	free(buffer);
	return 0;
}

int main()
{
	int nums[4] = {-1, 0, 1, -1};
	int numsSize = 4;
	int k = 2;
	// printArray(nums, numsSize);
	_Bool flag = containsNearbyDuplicate(nums, numsSize, k);
	// printArray(nums, numsSize);

	if (flag)
		puts("true");
	else
		puts("flase");

	return 0;
}