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

void moveZeroes(int *nums, int numsSize)
{
	int i, pos = 0, tmp;
	for (i = 0; i < numsSize; i++)
		if (nums[i] != 0)
		{
			tmp = nums[pos];
			nums[pos++] = nums[i];
			nums[i] = tmp;
		}
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("283.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int nums[100] = {0}, numsSize = 0;
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &(nums[numsSize]));
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

	moveZeroes(nums, numsSize);
	printf("zero-moved nums = ");
	printArray(nums, numsSize);

	return 0;
}