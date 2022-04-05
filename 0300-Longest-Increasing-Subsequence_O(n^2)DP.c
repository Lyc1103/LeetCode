#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (a > b ? a : b)

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

int cmpfunc(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

int lengthOfLIS(int *nums, int numsSize)
{
	int i, j, *tmp;
	int *buffer = (int *)malloc(numsSize * sizeof(int));
	for (i = 0; i < numsSize; i++)
		buffer[i] = nums[i];
	qsort(buffer, numsSize, sizeof(int), cmpfunc);
	int bufferSize = 1;
	for (i = 1; i < numsSize; i++)
		if (buffer[i] != buffer[i - 1])
			buffer[bufferSize++] = buffer[i];

	int *dp0 = (int *)calloc(numsSize, sizeof(int));
	int *dp1 = (int *)calloc(numsSize, sizeof(int));
	for (i = 0; i < bufferSize; i++)
	{
		if (nums[0] == buffer[i])
			dp0[0] = dp1[0] + 1;
		else
			dp0[0] = dp1[0];
		for (j = 1; j < numsSize; j++)
		{
			if (nums[j] == buffer[i])
				dp0[j] = dp1[j - 1] + 1;
			else
				dp0[j] = MAX(dp0[j - 1], dp1[j]);
		}

		tmp = dp1;
		dp1 = dp0;
		dp0 = tmp;
	}

	return dp1[numsSize - 1];
}

int main()
{
	int nums[100] = {0}, numsSize = 0;
	FILE *pfile = NULL;
	if ((pfile = fopen("300.txt", "r")) == NULL)
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

	printf("lengthOfLIS = %d\n", lengthOfLIS(nums, numsSize));

	return 0;
}