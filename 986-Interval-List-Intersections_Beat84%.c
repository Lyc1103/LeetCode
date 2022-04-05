// Reference: https://hackmd.io/@kenjin/Hye44cxXH
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)
void printMatrix_int(int **mat, int matSize, int matColSize);
void printArray_int(int *nums, int numsSize);

_Bool thereIsIntersection(int *first_segment, int *second_segment)
{
	if ((first_segment[0] <= second_segment[0] && second_segment[0] <= first_segment[1]) || (second_segment[0] <= first_segment[0] && first_segment[0] <= second_segment[1]))
		return 1;
	return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **intervalIntersection(int **firstList, int firstListSize, int *firstListColSize, int **secondList, int secondListSize, int *secondListColSize, int *returnSize, int **returnColumnSizes)
{
	int size = 1000;
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(size * sizeof(int));
	int **ret = (int **)malloc(size * sizeof(int *));

	int first_pos, second_pos;
	for (first_pos = 0, second_pos = 0; first_pos < firstListSize && second_pos < secondListSize;)
	{
		// printf("first_pos = %d, second_pos = %d\n", first_pos, second_pos);
		// printArray_int(firstList[first_pos], 2);
		// printArray_int(secondList[second_pos], 2);
		if (thereIsIntersection(firstList[first_pos], secondList[second_pos]))
		{
			// puts("There is intersection!");
			if (*returnSize >= size)
			{
				// puts("realloc");
				size *= 2;
				ret = realloc(ret, size * sizeof(int *));
				*returnColumnSizes = realloc(*returnColumnSizes, size * sizeof(int));
			}
			ret[*returnSize] = (int *)malloc(2 * sizeof(int));
			ret[*returnSize][0] = MAX(firstList[first_pos][0], secondList[second_pos][0]);
			ret[*returnSize][1] = MIN(firstList[first_pos][1], secondList[second_pos][1]);
			(*returnColumnSizes)[*returnSize] = 2;

			// update list value
			if (ret[*returnSize][1] < firstList[first_pos][1])
				firstList[first_pos][0] = ret[*returnSize][1] + 1;
			else
				first_pos++;
			if (ret[*returnSize][1] < secondList[second_pos][1])
				secondList[second_pos][0] = ret[*returnSize][1] + 1;
			else
				second_pos++;

			(*returnSize)++;
		}
		else // no intersection
		{
			if (firstList[first_pos][1] < secondList[second_pos][0])
				first_pos++;
			else
				second_pos++;
		}
	}
	return ret;
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
				printf("%2d,", mat[i][j]);
			printf("%2d]\n", mat[i][matColSize - 1]);
		}
	puts("  completely print.");
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
			printf("%2d,", nums[i]);
	}
	printf("%2d]", nums[numsSize - 1]);
	puts(" // completely print.");
	return;
}

int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize)
{
	int size = 10;
	*matSize = 0;
	int **mat = (int **)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
	{
		mat[i] = (int *)malloc(size * sizeof(int));
		*matColSize = (int *)calloc(size, sizeof(int));
	}
	char c;
	int ctr = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		while (!feof(pfile))
		{
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == '[')
				break;
		}
		while (!feof(pfile))
		{
			fscanf(pfile, "%d", &mat[*matSize][ctr]);
			printf("%d", mat[*matSize][ctr]);
			ctr++;
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				(*matColSize)[*matSize] = ctr;
				(*matSize)++;
				ctr = 0;
				break;
			}
		}
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	return mat;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("986.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int firstListSize, *firstListColSize, secondListSize, *secondListColSize, returnSize, *returnColumnSizes;
	int **firstList = dealWithInputFile_forMatrix(pfile, &firstListSize, &firstListColSize);
	int **secondList = dealWithInputFile_forMatrix(pfile, &secondListSize, &secondListColSize);
	puts("");

	puts("firstList:");
	printMatrix_int(firstList, firstListSize, firstListColSize[0]);
	puts("secondList:");
	printMatrix_int(secondList, secondListSize, secondListColSize[0]);

	int **ret = intervalIntersection(firstList, firstListSize, firstListColSize, secondList, secondListSize, secondListColSize, &returnSize, &returnColumnSizes);
	puts("result:");
	printMatrix_int(ret, returnSize, returnColumnSizes[0]);

	return 0;
}
