#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

int numberOfArithmeticSlices(int *nums, int numsSize)
{
	if (numsSize <= 2)
		return 0;
	int bufferSize = 30;
	int *buffer = (int *)calloc(bufferSize, sizeof(int));
	buffer[3] = 1;
	int i;
	for (i = 4; i < bufferSize; i++)
	{
		buffer[i] = buffer[i - 1] + (i - 2);
	}

	int pre_diff = nums[1] - nums[0];
	int res = 0, cnt = 2;
	for (i = 2; i < numsSize; i++)
	{
		if (nums[i] - nums[i - 1] == pre_diff)
		{
			cnt++;
			res += (buffer[cnt] - buffer[cnt - 1]);
		}
		else
		{
			cnt = 2;
			pre_diff = nums[i] - nums[i - 1];
		}
	}
	return res;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("413.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int flag = 0;
	int nums[100] = {0}, numsSize = 0;
	printf("input:\n");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			flag = 2;
			break;
		}
		else if (c == '[' || flag == 1)
		{
			fscanf(pfile, "%d", &(nums[numsSize]));
			printf("%d", nums[numsSize]);
			numsSize++;
			flag = 1;
		}
	}
	puts("");

	printf("nums = ");
	printArray(nums, numsSize);

	int res = numberOfArithmeticSlices(nums, numsSize);
	printf("res = %d\n", res);

	return 0;
}