#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
void printArray_int(int *nums, int numsSize);

#define MIN(a, b) (a < b ? a : b)

int minSubArrayLen(int target, int *nums, int numsSize)
{
	int sum = 0, res = INT_MAX;
	// sliding window
	for (int front = 0, rear = 0; rear < numsSize; rear++)
	{
		sum += nums[rear];
		if (sum >= target)
		{
			while (sum >= target && front <= rear)
				sum -= nums[front++];
			sum += nums[--front];
			printf("container: ");
			printArray_int(&(nums[front]), rear - front + 1);
			res = MIN(res, rear - front + 1);
		}
	}

	return res == INT_MAX ? 0 : res;
}

int *dealWithInputFile_ForNums(FILE *pfile, int *numsSize)
{
	char c;
	int sum = 0, flag = 0;
	*numsSize = 0;
	int *nums = (int *)malloc(50 * sizeof(int));
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
		{
			if (flag)
			{
				nums[*numsSize] = sum;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum;
			(*numsSize)++;
			sum = 0;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	return nums;
}

void printArray_int(int *nums, int numsSize)
{
	if (numsSize == 0)
	{
		puts("[]");
		return;
	}
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%2d,", nums[i]);
	}
	printf("%2d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("209.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	printf("input: ");
	int numsSize, target;
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &target);
	printf(" %d", target);
	int *nums = dealWithInputFile_ForNums(pfile, &numsSize);
	puts("");

	printf("min sub array len = %d\n", minSubArrayLen(target, nums, numsSize));

	return 0;
}