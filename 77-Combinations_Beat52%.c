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

int C(int m, int n)
{
	int *pre_row = (int *)calloc(20, sizeof(int));
	int *cur_row = (int *)calloc(20, sizeof(int));
	int i, j, *tmp;
	if ((n == 0) || (m == n))
		return 1;
	pre_row[0] = 1;
	cur_row[0] = 1;
	n = m - n < n ? m - n : n;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= i && j <= n; j++)
			cur_row[j] = pre_row[j] + pre_row[j - 1];
		tmp = pre_row;
		pre_row = cur_row;
		cur_row = tmp;
	}
	return pre_row[n];
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

void DFS(int **ret, int *ctr, int n, int k, int pos, Stack *sta)
{
	if (k == 0)
	{
		// printElementsInStack(sta);
		cpyElementsFromStackToArray(sta, ret, ctr);
		return;
	}
	for (int i = pos; i <= n; i++)
	{
		pushToStack(sta, i);
		DFS(ret, ctr, n, k - 1, i + 1, sta);
		popFromStack(sta);
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combine(int n, int k, int *returnSize, int **returnColumnSizes)
{
	int i, j, size = C(n, k);
	printf("size = %d\n", size);
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(size * sizeof(int));
	int **ret = (int **)malloc(size * sizeof(int *));
	for (i = 0; i < size; i++)
	{
		ret[i] = (int *)malloc(k * sizeof(int));
		(*returnColumnSizes)[i] = k;
	}

	Stack *sta = createStack(k + 1);
	DFS(ret, returnSize, n, k, 1, sta);
	puts("dfs completed.");
	return ret;
}

void dealWithInputFile(FILE *pfile, int *n, int *k)
{
	char c;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", n);
	printf(" %d", *n);
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			break;
	}
	fscanf(pfile, " %d", k);
	printf(" %d", *k);
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
	if ((pfile = fopen("77.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int n, k;
	dealWithInputFile(pfile, &n, &k);
	printf("n = %d, k = %d\n", n, k);

	int returnSize, *returnColumnSize;
	int **ret = combine(n, k, &returnSize, &returnColumnSize);
	printMatrix(ret, returnSize, returnColumnSize[0]);
	return 0;
}