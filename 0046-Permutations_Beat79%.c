#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void printArray_int(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		if (nums[i] == INT_MIN)
			printf("null,");
		else
			printf("%d,", nums[i]);
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
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
	int *data;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->data = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int data)
{
	(sta->top)++;
	sta->data[sta->top] = data;
	return;
}

int popFromStack(Stack *sta)
{
	(sta->top)--;
	return sta->data[(sta->top) + 1];
}

void freeStack(Stack *sta)
{
	free(sta->data);
	free(sta);
	return;
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta = []");
		return;
	}
	printf("sta = [");
	int i;
	for (i = 0; i < sta->top; i++)
		printf("%d,", sta->data[i]);
	printf("%d]\n", sta->data[i]);
}

void cpyElementsFromStackToArray(Stack *sta, int **ret, int *ctr)
{
	for (int i = 0; i <= sta->top; i++)
		ret[*ctr][i] = sta->data[i];
	(*ctr)++;
	return;
}

void DFS(int *nums, int numsSize, int **ret, int *ctr, _Bool *visited, int len, Stack *sta)
{
	if (len == 0)
	{
		// printElementsInStack(sta);
		cpyElementsFromStackToArray(sta, ret, ctr);
		return;
	}
	for (int i = 0; i < numsSize; i++)
	{
		if (!visited[i])
		{
			visited[i] = 1;
			pushToStack(sta, nums[i]);
			DFS(nums, numsSize, ret, ctr, visited, len - 1, sta);
			popFromStack(sta);
			visited[i] = 0;
		}
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
	int i, j, size = P(numsSize, numsSize);
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(size * sizeof(int));
	int **ret = (int **)malloc(size * sizeof(int *));
	for (i = 0; i < size; i++)
	{
		ret[i] = (int *)malloc(numsSize * sizeof(int));
		(*returnColumnSizes)[i] = numsSize;
	}
	_Bool *visited = (_Bool *)calloc(numsSize, sizeof(_Bool));
	Stack *sta = createStack(size);
	DFS(nums, numsSize, ret, returnSize, visited, numsSize, sta);
	return ret;
}

void dealWithInputFile_ForNums(FILE *pfile, int *nums, int *numsSize)
{
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%d", &(nums[*numsSize]));
		printf("%d", nums[*numsSize]);
		(*numsSize)++;
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");
	return;
}

void printMatrix(int **mat, int matSize, int matColSize)
{
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
	if ((pfile = fopen("46.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int nums[50] = {0}, numsSize = 0;
	dealWithInputFile_ForNums(pfile, nums, &numsSize);
	printf("nums: ");
	printArray_int(nums, numsSize);

	int returnSize, *returnColumnSize;
	int **ret = permute(nums, numsSize, &returnSize, &returnColumnSize);
	printMatrix(ret, returnSize, returnColumnSize[0]);
	return 0;
}