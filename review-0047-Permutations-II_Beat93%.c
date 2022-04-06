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

int P(int m, int n)
{
	int i, res = 1;
	for (i = m; i > m - n; i--)
	{
		res *= i;
	}
	return res;
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

void cpyElementsFromStack(Stack *sta, int **ret, int *index)
{
	for (int i = 0; i <= sta->top; i++)
		ret[*index][i] = sta->pos[i];
	(*index)++;
	return;
}

void DFSFindSubsets(int *nums, int numsSize, int ***ret, int *size, int *returnSize, int **returnColSize, _Bool *visited, int len, Stack *sta)
{
	if (len == 0)
	{
		// printElementsInStack(sta);
		if (*returnSize >= *size)
		{
			*size *= 2;
			*ret = realloc(*ret, *size * sizeof(int *));
			*returnColSize = realloc(*returnColSize, *size * sizeof(int));
		}
		(*ret)[*returnSize] = (int *)malloc(numsSize * sizeof(int));
		(*returnColSize)[*returnSize] = numsSize;
		cpyElementsFromStack(sta, *ret, returnSize);
		return;
	}
	for (int i = 0; i < numsSize; i++)
	{
		if (visited[i])
			continue;
		if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])
			continue;
		visited[i] = 1;
		pushToStack(sta, nums[i]);
		DFSFindSubsets(nums, numsSize, ret, size, returnSize, returnColSize, visited, len - 1, sta);
		popFromStack(sta);
		visited[i] = 0;
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permuteUnique(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	qsort(nums, numsSize, sizeof(int), cmpFunction);

	int i, j, size = 200;
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(size * sizeof(int));
	int **ret = (int **)malloc(size * sizeof(int *));
	_Bool *visited = (_Bool *)calloc(numsSize, sizeof(_Bool));
	Stack *sta = createStack(numsSize);
	DFSFindSubsets(nums, numsSize, &ret, &size, returnSize, returnColumnSizes, visited, numsSize, sta);
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
	puts("");
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
	if ((pfile = fopen("0047.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int numsSize;
	int *nums = dealWithInputFile_ForNums(pfile, &numsSize);
	printArray_int(nums, numsSize);

	int returnSize, *returnColumnSize;
	int **ret = permuteUnique(nums, numsSize, &returnSize, &returnColumnSize);
	printMatrix_int(ret, returnSize, returnColumnSize);

	return 0;
}