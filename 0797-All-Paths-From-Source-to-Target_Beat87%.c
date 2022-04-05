#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

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

void pushToStack(Stack *sta, int index)
{
	(sta->top)++;
	sta->data[sta->top] = index;
	return;
}

int popFromStack(Stack *sta)
{
	(sta->top)--;
	return sta->data[sta->top + 1];
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
		printf("%d, ", sta->data[i]);
	printf("%d]\n", sta->data[sta->top]);
	return;
}

void cpyElementsFromStack(Stack *sta, int **ret_mat, int index)
{
	for (int i = 0; i <= sta->top; i++)
		ret_mat[index][i] = sta->data[i];
	return;
}

void DFS(int **graph, int graphSize, int *graphColSize, int cur_val, Stack *sta, int ***ret, int *malloc_size, int *returnSize, int **returnColumnSizes)
{
	if (cur_val == graphSize - 1)
	{
		// printElementsInStack(sta);
		if (*returnSize >= *malloc_size)
		{
			(*malloc_size) *= 2;
			*ret = realloc(*ret, (*malloc_size) * sizeof(int *));
			*returnColumnSizes = realloc(*returnColumnSizes, (*malloc_size) * sizeof(int));
		}
		(*ret)[*returnSize] = (int *)malloc(((sta->top) + 1) * sizeof(int));
		(*returnColumnSizes)[*returnSize] = (sta->top) + 1;
		cpyElementsFromStack(sta, *ret, *returnSize);
		(*returnSize)++;
		return;
	}

	for (int i = 0; i < graphColSize[cur_val]; i++)
	{
		pushToStack(sta, graph[cur_val][i]);
		DFS(graph, graphSize, graphColSize, graph[cur_val][i], sta, ret, malloc_size, returnSize, returnColumnSizes);
		popFromStack(sta);
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **allPathsSourceTarget(int **graph, int graphSize, int *graphColSize, int *returnSize, int **returnColumnSizes)
{
	int malloc_size = 1000;
	int **ret = (int **)malloc(malloc_size * sizeof(int *));
	*returnSize = 0;
	*returnColumnSizes = (int *)malloc(malloc_size * sizeof(int));
	Stack *sta = createStack(graphSize + 1);
	pushToStack(sta, 0);
	DFS(graph, graphSize, graphColSize, 0, sta, &ret, &malloc_size, returnSize, returnColumnSizes);
	return ret;
}

int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize)
{
	int size = 100;
	*matSize = 0;
	int **mat = (int **)malloc(size * sizeof(int *));
	for (int i = 0; i < size; i++)
	{
		mat[i] = (int *)malloc(size * sizeof(int));
		*matColSize = (int *)calloc(size, sizeof(int));
	}
	char c;
	int ctr = 0, sum = 0, flag = 0;
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
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				if (flag)
				{
					mat[*matSize][ctr] = sum;
					(*matColSize)[*matSize] = ctr + 1;
					ctr = 0;
					sum = 0;
					flag = 0;
				}
				(*matSize)++;
				break;
			}
			if (c == ',')
			{
				mat[*matSize][ctr] = sum;
				ctr++;
				sum = 0;
			}
			else
			{

				sum = sum * 10 + (c - '0');
				flag = 1;
			}
		}
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == ']')
			break;
	}
	puts("");
	return mat;
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
	if ((pfile = fopen("0797.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int graphSize, *graphColSize;
	int **graph = dealWithInputFile_forMatrix(pfile, &graphSize, &graphColSize);
	printMatrix_int(graph, graphSize, graphColSize);

	int returnSize, *returnColumnSizes;
	int **ret = allPathsSourceTarget(graph, graphSize, graphColSize, &returnSize, &returnColumnSizes);
	printMatrix_int(ret, returnSize, returnColumnSizes);

	return 0;
}