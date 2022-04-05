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
	if (nums[0] >= numsSize - 1)
		return 1;

	int front = 1, rear = nums[0], farthest = nums[0], cnt = 1;
	while (1)
	{
		for (int i = front; i <= rear && i < numsSize - 1; i++)
		{
			printf("%d, ", i);
			farthest = farthest > i + nums[i] ? farthest : i + nums[i];
		}
		printf("farthest = %d\n", farthest);
		cnt++;
		if (farthest >= numsSize - 1)
			return cnt;

		front = rear + 1;
		rear = farthest;
	}
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
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c%d", &c, &nums[numsSize]);
		printf("%d ", nums[numsSize]);
		numsSize++;
	}
	puts("");

	int min_step = jump(nums, numsSize);
	printf("min_step = %d\n", min_step);

	return 0;
}