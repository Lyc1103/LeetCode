#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
void printArray_int(int *nums, int numsSize);
void printMatrix_int(int **mat, int matSize, int *matColSize);

int cmpFunction(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

typedef struct stackInformation
{
	int top;
	int *pos;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->pos = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int index)
{
	(sta->top)++;
	sta->pos[sta->top] = index;
	return;
}

int popFromStack(Stack *sta)
{
	(sta->top)--;
	return sta->pos[sta->top + 1];
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta: []");
		return;
	}
	printf("sta: [");
	for (int i = 0; i < sta->top; i++)
		printf("%d, ", sta->pos[i]);
	printf("%d]\n", sta->pos[sta->top]);
	return;
}

void cpyElementsFromStack(Stack *sta, int **ret, int *returnSize, int **returnColSize)
{
	for (int i = 0; i <= sta->top; i++)
		ret[*returnSize][i] = sta->pos[i];
	(*returnColSize)[*returnSize] = sta->top + 1;
	(*returnSize)++;
	return;
}

void DFSFindSum(int *candidates, int candidatesSize, int ***ret, const int malloc_size, int *realloc_size, int *returnSize, int **returnColSize, int remainder, int pos, Stack *sta)
{
	if (remainder == 0)
	{
		// printElementsInStack(sta);
		if (*returnSize >= *realloc_size)
		{
			*realloc_size *= 2;
			*ret = realloc(*ret, *realloc_size * sizeof(int *));
			*returnColSize = realloc(*returnColSize, *realloc_size * sizeof(int));
		}
		(*ret)[*returnSize] = (int *)malloc(malloc_size * sizeof(int));
		cpyElementsFromStack(sta, *ret, returnSize, returnColSize);
		return;
	}
	if (remainder < 0 || pos >= candidatesSize)
		return;
	pushToStack(sta, candidates[pos]);
	DFSFindSum(candidates, candidatesSize, ret, malloc_size, realloc_size, returnSize, returnColSize, remainder - candidates[pos], pos, sta);
	popFromStack(sta);
	DFSFindSum(candidates, candidatesSize, ret, malloc_size, realloc_size, returnSize, returnColSize, remainder, pos + 1, sta);

	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum(int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
	qsort(candidates, candidatesSize, sizeof(int), cmpFunction);

	int i, j, malloc_size = target / candidates[0] + 1;
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(malloc_size * sizeof(int));
	int **ret = (int **)malloc(malloc_size * sizeof(int *));
	Stack *sta = createStack(target);
	DFSFindSum(candidates, candidatesSize, &ret, malloc_size, &malloc_size, returnSize, returnColumnSizes, target, 0, sta);
	return ret;
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
		puts("nums: []");
		return;
	}
	printf("nums: [");
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

void printMatrix_int(int **mat, int matSize, int *matColSize)
{
	if (matSize == 0)
		puts("mat:\n    []");
	else
	{
		printf("mat:  ");
		for (int i = 0; i < 5; i++)
			printf("  %d", i);
		puts("");
		for (int i = 0; i < matSize; i++)
		{
			if (matColSize[i] == 0)
			{
				printf("    %d []\n", i);
				continue;
			}
			printf("    %d [", i);
			for (int j = 0; j < matColSize[i] - 1; j++)
				printf("%2d,", mat[i][j]);
			printf("%2d]\n", mat[i][matColSize[i] - 1]);
		}
	}
	puts("    completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("0039.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int candidatesSize, target;
	int *candidates = dealWithInputFile_ForNums(pfile, &candidatesSize);
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, "%d", &target);
	printf(" %d\n", target);
	printArray_int(candidates, candidatesSize);
	printf("target = %d\n", target);

	int returnSize, *returnColumnSize;
	int **ret = combinationSum(candidates, candidatesSize, target, &returnSize, &returnColumnSize);
	printMatrix_int(ret, returnSize, returnColumnSize);

	return 0;
}