#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void dealWithInputFile_ForNums(FILE *pfile, int *nums, int *numsSize);
void printArray_int(int *nums, int numsSize);
void printMatrix_int(int **mat, int matSize, int matColSize);

int cmpFunction(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	qsort(nums, numsSize, sizeof(int), cmpFunction);

	int i, j, bias = 200000;
	int cnt_table[400001] = {0};
	for (i = 0; i < numsSize; i++)
		cnt_table[nums[i] + bias] += 1;

	int size = 1000, target;
	int **ret = (int **)malloc(size * sizeof(int *));
	*returnColumnSizes = (int *)malloc(size * sizeof(int));
	*returnSize = 0;
	for (i = 0; i < numsSize; i++)
	{
		if (i > 0 && nums[i] == nums[i - 1])
			continue;

		for (j = i + 1; j < numsSize; j++)
		{
			if (nums[j] == nums[j - 1] && j != i + 1)
				continue;

			target = 0 - nums[i] - nums[j];
			// printf("nums[%d] = %d, nums[%d] = %d, target = %d\n", i, nums[i], j, nums[j], target);
			if (target < nums[j])
				continue;

			if (cnt_table[target + bias] >= 1 + (target == nums[i]) + (target == nums[j]))
			{
				if (*returnSize >= size)
				{
					size *= 2;
					ret = realloc(ret, size * sizeof(int *));
					*returnColumnSizes = realloc(*returnColumnSizes, size * sizeof(int *));
				}
				ret[*returnSize] = (int *)malloc(3 * sizeof(int));
				ret[*returnSize][0] = nums[i];
				ret[*returnSize][1] = nums[j];
				ret[*returnSize][2] = target;
				(*returnColumnSizes)[*returnSize] = 3;
				// printf("ret[%d] = [%d, %d, %d]\n", *returnSize, nums[i], nums[j], target);
				*returnSize += 1;
			}
		}
	}

	return ret;
}

void dealWithInputFile_ForNums(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	int sum = 0, flag = 0, neg = 1;
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
		if (c == '-')
		{
			neg = -1;
			continue;
		}
		if (c == ']')
		{
			if (flag)
			{
				nums[*numsSize] = sum * neg;
				(*numsSize)++;
			}
			break;
		}
		if (c == ',')
		{
			nums[*numsSize] = sum * neg;
			(*numsSize)++;
			sum = 0;
			neg = 1;
		}
		else
		{
			sum = sum * 10 + (c - '0');
			flag = 1;
		}
	}
	puts("");
	return;
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
			printf("%d,", nums[i]);
	}
	printf("%d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

void printMatrix_int(int **mat, int matSize, int matColSize)
{
	if (matSize == 0)
		puts("  []");
	else
		for (int i = 0; i < matSize; i++)
		{
			printf("  row%d = [", i);
			for (int j = 0; j < matColSize - 1; j++)
				printf("%d,", mat[i][j]);
			printf("%d]\n", mat[i][matColSize - 1]);
		}
	puts("  completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("15.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[55000] = {0}, numsSize = 0;
	dealWithInputFile_ForNums(pfile, nums, &numsSize);
	printf("nums: ");
	printArray_int(nums, numsSize);

	int returnSize, *returnColumnSize;
	int **ret = threeSum(nums, numsSize, &returnSize, &returnColumnSize);
	puts("ret:");
	printMatrix_int(ret, returnSize, returnColumnSize[0]);

	return 0;
}