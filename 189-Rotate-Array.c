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

void reverse(int *nums, int f, int r)
{
	int tmp;
	while (f <= r)
	{
		tmp = nums[f];
		nums[f] = nums[r];
		nums[r] = tmp;
		f++;
		r--;
	}
	return;
}

void rotate(int *nums, int numsSize, int k)
{
	if (numsSize == 1)
		return;
	k %= numsSize;
	if (k == 0)
		return;
	reverse(nums, 0, numsSize - 1 - k);
	reverse(nums, numsSize - k, numsSize - 1);
	reverse(nums, 0, numsSize - 1);
	return;
}

int main()
{
	FILE *pfile = NULL;
	if ((pfile = fopen("189.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int k;
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
	fscanf(pfile, " %d", &k);
	printf(" %d", k);
	puts("");

	printf("nums = ");
	printArray(nums, numsSize);
	printf("k = %d\n", k);

	rotate(nums, numsSize, k);
	printf("rotated nums = ");
	printArray(nums, numsSize);

	return 0;
}