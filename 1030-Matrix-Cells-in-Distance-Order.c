#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void printArray(int *nums, int numsSize)
{
	printf("[");
	for (int i = 0; i < numsSize - 1; i++)
	{
		printf("%d", nums[i]);
		printf(",");
	}
	printf("%d]\n", nums[numsSize - 1]);
	return;
}

typedef struct
{
	int16_t **data;
	int16_t top;
} Stack;

void Push(Stack *sta, int16_t x, int16_t y)
{
	(sta->top)++;
	sta->data[0][sta->top] = x;
	sta->data[1][sta->top] = y;
	return;
}

void Pop(Stack *sta, int16_t *x, int16_t *y)
{
	*x = sta->data[0][sta->top];
	*y = sta->data[1][sta->top];
	(sta->top)--;
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **allCellsDistOrder(int rows, int cols, int rCenter, int cCenter, int *returnSize, int **returnColumnSizes)
{
	Stack *S = (Stack *)malloc(sizeof(Stack));
	Stack *T = (Stack *)malloc(sizeof(Stack));
	S->top = -1;
	S->data = (int16_t **)malloc(2 * sizeof(int16_t *));
	S->data[0] = (int16_t *)calloc(rows * cols, sizeof(int16_t));
	S->data[1] = (int16_t *)calloc(rows * cols, sizeof(int16_t));
	T->top = -1;
	T->data = (int16_t **)malloc(2 * sizeof(int16_t *));
	T->data[0] = (int16_t *)calloc(rows * cols, sizeof(int16_t));
	T->data[1] = (int16_t *)calloc(rows * cols, sizeof(int16_t));

	int **res = (int **)malloc(rows * cols * sizeof(int *));
	*returnColumnSizes = (int *)calloc(rows * cols, sizeof(int)); // Why can I use calloc ?
	for (int i = 0; i < rows * cols; i++)
	{
		res[i] = (int *)calloc(2, sizeof(int));
		(*returnColumnSizes)[i] = 2;
	}
	res[0][0] = rCenter;
	res[0][1] = cCenter;
	*returnSize = 0;

	int16_t **mat = (int16_t **)calloc(rows, sizeof(int16_t *));
	for (int i = 0; i < rows; i++)
	{
		mat[i] = (int16_t *)calloc(cols, sizeof(int16_t));
	}
	mat[rCenter][cCenter] = 1;

	int16_t x = (int16_t)rCenter,
		y = (int16_t)cCenter;
	Push(S, x, y);
	while (S->top != -1 || T->top != -1)
	{
		while (T->top != -1)
		{
			Pop(T, &x, &y);
			// printf("x = %d, y = %d, returnSize = %d\n", x, y, *returnSize);
			res[*returnSize][0] = (int)x;
			res[*returnSize][1] = (int)y;
			(*returnSize)++;
			if (0 <= x - 1 && x - 1 < rows && mat[x - 1][y] == 0)
			{
				mat[x - 1][y] = 1;
				Push(S, x - 1, y);
			}
			if (0 <= x + 1 && x + 1 < rows && mat[x + 1][y] == 0)
			{
				mat[x + 1][y] = 1;
				Push(S, x + 1, y);
			}
			if (0 <= y - 1 && y - 1 < cols && mat[x][y - 1] == 0)
			{
				mat[x][y - 1] = 1;
				Push(S, x, y - 1);
			}
			if (0 <= y + 1 && y + 1 < cols && mat[x][y + 1] == 0)
			{
				mat[x][y + 1] = 1;
				Push(S, x, y + 1);
			}
		}
		while (S->top != -1)
		{
			Pop(S, &x, &y);
			Push(T, x, y);
		}
	}
	// printf("returnSize = %d\n", *returnSize);

	return res;
}

int main()
{
	int rows = 2;
	int cols = 3;
	int rCenter = 1;
	int cCenter = 2;
	int returnSize, *returnColumnSizes;
	int **res = allCellsDistOrder(rows, cols, rCenter, cCenter, &returnSize, &returnColumnSizes);
	for (int i = 0; i < returnSize; i++)
	{
		printf("row %d: ", i);
		// printf("returnColumnSize[i] = %d", returnColumnSizes[i]);
		printArray(res[i], returnColumnSizes[i]);
	}

	return 0;
}