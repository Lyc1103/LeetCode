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

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int partition(int *nums, int s, int t)
{
	int tmp, half = (s + t) / 2;
	int cmp1 = nums[s], cmp2 = nums[half], cmp3 = nums[t];
	int pivot_v = cmp3;
	if (cmp1 > cmp2 && cmp2 > cmp3)
	{
		pivot_v = cmp2;
		swap(&nums[half], &nums[t]);
	}
	else if (cmp2 > cmp1 && cmp1 > cmp3)
	{
		pivot_v = cmp1;
		swap(&nums[s], &nums[t]);
	}
	else if (cmp3 > cmp1 && cmp1 > cmp2)
	{
		pivot_v = cmp1;
		swap(&nums[s], &nums[t]);
	}
	else if (cmp3 > cmp2 && cmp2 > cmp1)
	{
		pivot_v = cmp2;
		swap(&nums[half], &nums[t]);
	}

	int i = s - 1;
	for (int j = s; j < t; j++)
	{
		if (nums[j] < pivot_v)
		{
			i++;
			swap(&nums[i], &nums[j]);
		}
	}
	swap(&nums[i + 1], &nums[t]);

	return i + 1;
}

void quickSort(int *nums, int s, int t)
{
	if (s < t)
	{
		int pivot = partition(nums, s, t);
		quickSort(nums, s, pivot - 1);
		quickSort(nums, pivot + 1, t);
	}
	return;
}

int deleteAndEarn(int *nums, int numsSize)
{
	// Step 1: Sorted array
	quickSort(nums, 0, numsSize - 1);
	printf("sorted nums: ");
	printArray(nums, numsSize);

	// Step 2: count sum
	int **index_earn_buffer = (int **)malloc(2 * sizeof(int *));
	index_earn_buffer[0] = (int *)calloc(nums[numsSize - 1] - nums[0] + 1, sizeof(int));
	index_earn_buffer[1] = (int *)calloc(nums[numsSize - 1] - nums[0] + 1, sizeof(int));
	int16_t i, j, cnt = 0;
	index_earn_buffer[0][cnt] = nums[0];
	index_earn_buffer[1][cnt] = nums[0];
	for (i = 1; i < numsSize; i++)
	{
		if (nums[i] == index_earn_buffer[0][cnt])
			index_earn_buffer[1][cnt] += nums[i];
		else
		{
			cnt++;
			index_earn_buffer[0][cnt] = nums[i];
			index_earn_buffer[1][cnt] = nums[i];
		}
	}
	cnt++;
	printf("index: ");
	printArray(index_earn_buffer[0], cnt);
	printf("sum:   ");
	printArray(index_earn_buffer[1], cnt);

	// Step 3: DP
	if (cnt == 1)
		return index_earn_buffer[1][0];
	int dp_cur, dp_pre, tmp;
	dp_pre = index_earn_buffer[1][0];
	if (index_earn_buffer[0][1] == index_earn_buffer[0][0] + 1)
		dp_cur = index_earn_buffer[1][0] > index_earn_buffer[1][1] ? index_earn_buffer[1][0] : index_earn_buffer[1][1];
	else
		dp_cur = dp_pre + index_earn_buffer[1][1];

	printf("i = 1, dp_cur = %d, dp_pre = %d\n", dp_cur, dp_pre);
	for (i = 2; i < cnt; i++)
	{
		tmp = dp_cur;
		if (index_earn_buffer[0][i] == index_earn_buffer[0][i - 1] + 1)
		{
			printf("here1: ");
			dp_cur = index_earn_buffer[1][i] + dp_pre;
			dp_pre = tmp;
			dp_cur = dp_cur > dp_pre ? dp_cur : dp_pre;
		}
		else
		{
			printf("here2: ");
			dp_cur += index_earn_buffer[1][i];
			dp_pre = tmp;
		}
		printf("i = %d, index_i = %d, dp_cur = %d, dp_pre = %d\n", i, index_earn_buffer[0][i], dp_cur, dp_pre);
	}
	return dp_cur;
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("740.txt", "r")) == NULL)
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

	int res = deleteAndEarn(nums, numsSize);
	printf("max-earning = %d\n", res);
}