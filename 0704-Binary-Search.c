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

int search(int *nums, int numsSize, int target)
{
	int front = 0, rear = numsSize - 1, mid;
	while (front < rear)
	{
		mid = (front + rear) / 2;
		if (target == nums[mid])
			return mid;
		if (target < nums[mid])
			rear = mid - 1;
		else if (target > nums[mid])
			front = mid + 1;
	}
	return -1;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("704.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int target;
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
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", &target);
	printf(" %d", target);
	puts("");

	printf("nums = ");
	printArray(nums, numsSize);
	printf("target = %d\n", target);

	printf("position = %d\n", search(nums, numsSize, target));

	return 0;
}