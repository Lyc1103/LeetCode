#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackInformation
{
	int top;
	int **pos;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->pos = (int **)malloc(2 * sizeof(int *));
	sta->pos[0] = (int *)malloc(size * sizeof(int));
	sta->pos[1] = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int pos_x, int pos_y)
{
	(sta->top)++;
	sta->pos[0][sta->top] = pos_x;
	sta->pos[1][sta->top] = pos_y;
	return;
}

void popFromStack(Stack *sta, int *ret_x, int *ret_y)
{
	*ret_x = sta->pos[0][sta->top];
	*ret_y = sta->pos[1][sta->top];
	(sta->top)--;
	return;
}

int shortestPathBinaryMatrix(int **grid, int gridSize, int *gridColSize)
{
	if (grid[0][0] || grid[gridSize - 1][gridColSize[0] - 1])
		return -1;

	Stack *s = createStack(gridSize * gridColSize[0]);
	Stack *t = createStack(gridSize * gridColSize[0]);
	grid[0][0] = 1;
	pushToStack(t, 0, 0);

	int cur_x, cur_y;
	while (!isEmptyStack(s) || !isEmptyStack(t))
	{
		;
		while (!isEmptyStack(t))
		{
			popFromStack(t, &cur_x, &cur_y);
			// printf("cur_x = %d, cur_y = %d\n", cur_x, cur_y);
			if (cur_x == gridSize - 1 && cur_y == gridColSize[0] - 1)
				return grid[gridSize - 1][gridColSize[0] - 1];

			// ES
			if (cur_x + 1 < gridSize && cur_y + 1 < gridColSize[0] && grid[cur_x + 1][cur_y + 1] == 0)
			{
				grid[cur_x + 1][cur_y + 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x + 1, cur_y + 1);
			}
			// S
			if (cur_x + 1 < gridSize && grid[cur_x + 1][cur_y] == 0)
			{
				grid[cur_x + 1][cur_y] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x + 1, cur_y);
			}
			// E
			if (cur_y + 1 < gridColSize[0] && grid[cur_x][cur_y + 1] == 0)
			{
				grid[cur_x][cur_y + 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x, cur_y + 1);
			}
			// WS
			if (cur_x + 1 < gridSize && cur_y > 0 && grid[cur_x + 1][cur_y - 1] == 0)
			{
				grid[cur_x + 1][cur_y - 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x + 1, cur_y - 1);
			}
			// EN
			if (cur_x > 0 && cur_y + 1 < gridColSize[0] && grid[cur_x - 1][cur_y + 1] == 0)
			{
				grid[cur_x - 1][cur_y + 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x - 1, cur_y + 1);
			}
			// W
			if (cur_y > 0 && grid[cur_x][cur_y - 1] == 0)
			{
				grid[cur_x][cur_y - 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x, cur_y - 1);
			}
			// N
			if (cur_x > 0 && grid[cur_x - 1][cur_y] == 0)
			{
				grid[cur_x - 1][cur_y] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x - 1, cur_y);
			}
			// WN
			if (cur_x > 0 && cur_y > 0 && grid[cur_x - 1][cur_y - 1] == 0)
			{
				grid[cur_x - 1][cur_y - 1] = grid[cur_x][cur_y] + 1;
				pushToStack(s, cur_x - 1, cur_y - 1);
			}
		}

		while (!isEmptyStack(s))
		{
			popFromStack(s, &cur_x, &cur_y);
			pushToStack(t, cur_x, cur_y);
		}
	}
	return -1;
}

int **dealWithInputFile_forMatrix(FILE *pfile, int *matSize, int **matColSize)
{
	int size = 10;
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
	puts("");
	return mat;
}

void printMatrix_int(int **mat, int matSize, int matColSize)
{
	if (matSize == 0)
		puts("mat:\n    []");
	else
	{
		printf("mat:  ");
		for (int i = 0; i < matColSize; i++)
			printf("  %d", i);
		puts("");
		for (int i = 0; i < matSize; i++)
		{
			printf("    %d [", i);
			for (int j = 0; j < matColSize - 1; j++)
				printf("%2d,", mat[i][j]);
			printf("%2d]\n", mat[i][matColSize - 1]);
		}
	}
	puts("    completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("1091.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int gridSize, *gridColSize;
	int **grid = dealWithInputFile_forMatrix(pfile, &gridSize, &gridColSize);
	printMatrix_int(grid, gridSize, gridColSize[0]);

	printf("shortest path len = %d\n", shortestPathBinaryMatrix(grid, gridSize, gridColSize));

	return 0;
}