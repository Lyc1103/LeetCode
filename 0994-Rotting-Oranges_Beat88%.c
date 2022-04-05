#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct stackInformation
{
	int top;
	int **position;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->position = (int **)malloc(2 * sizeof(int *));
	sta->position[0] = (int *)malloc(size * sizeof(int));
	sta->position[1] = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int x, int y)
{
	(sta->top)++;
	sta->position[0][sta->top] = x;
	sta->position[1][sta->top] = y;
	return;
}

void popFromStack(Stack *sta, int *x, int *y)
{
	if (isEmptyStack(sta))
	{
		puts("Stack is empty. Pop from stack error!");
	}
	(sta->top)--;
	*x = sta->position[0][sta->top + 1];
	*y = sta->position[1][sta->top + 1];
	return;
}

void freeStack(Stack *sta)
{
	free(sta->position[0]);
	free(sta->position[1]);
	free(sta->position);
	free(sta);
	return;
}

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta.top = -1, sta =[]");
		return;
	}
	printf("sta->top = %d, sta = [", sta->top);
	int i;
	for (i = 0; i < sta->top; i++)
		printf("(%d, %d), ", sta->position[0][i], sta->position[1][i]);
	printf("(%d, %d)]\n", sta->position[0][i], sta->position[1][i]);
	return;
}

int orangesRotting(int **grid, int gridSize, int *gridColSize)
{
	int i, j, ctr = 0;
	Stack *s = createStack(gridSize * gridColSize[0]);
	Stack *t = createStack(gridSize * gridColSize[0]);
	for (i = 0; i < gridSize; i++)
		for (j = 0; j < gridColSize[0]; j++)
			if (grid[i][j] == 2)
				pushToStack(t, i, j);

	while (!isEmptyStack(s) || !isEmptyStack(t))
	{
		int cur_x, cur_y;
		while (!isEmptyStack(t))
		{
			popFromStack(t, &cur_x, &cur_y);
			if (cur_x > 0 && grid[cur_x - 1][cur_y] == 1)
			{
				grid[cur_x - 1][cur_y] = 2;
				pushToStack(s, cur_x - 1, cur_y);
			}
			if (cur_x + 1 < gridSize && grid[cur_x + 1][cur_y] == 1)
			{
				grid[cur_x + 1][cur_y] = 2;
				pushToStack(s, cur_x + 1, cur_y);
			}
			if (cur_y > 0 && grid[cur_x][cur_y - 1] == 1)
			{
				grid[cur_x][cur_y - 1] = 2;
				pushToStack(s, cur_x, cur_y - 1);
			}
			if (cur_y + 1 < gridColSize[0] && grid[cur_x][cur_y + 1] == 1)
			{
				grid[cur_x][cur_y + 1] = 2;
				pushToStack(s, cur_x, cur_y + 1);
			}
		}
		if (!isEmptyStack(s))
			ctr++;
		while (!isEmptyStack(s))
		{
			popFromStack(s, &cur_x, &cur_y);
			pushToStack(t, cur_x, cur_y);
		}
	}
	free(s);
	free(t);

	for (i = 0; i < gridSize; i++)
		for (j = 0; j < gridColSize[0]; j++)
			if (grid[i][j] == 1)
				return -1;
	return ctr;
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
	*matSize = 0;
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

int main()
{
	FILE *pfile;
	if ((pfile = fopen("994.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int gridSize, *gridColSize;
	int **grid = dealWithInputFile_forMatrix(pfile, &gridSize, &gridColSize);
	printf("gridSize = %d, gridColSize = %d\n", gridSize, gridColSize[0]);
	puts("matrix:");
	printMatrix(grid, gridSize, gridColSize[0]);

	// // test
	// Stack *sta = createStack(10);
	// pushToStack(sta, 0, 0);
	// printElementsInStack(sta);
	// pushToStack(sta, 1, 1);
	// printElementsInStack(sta);
	// pushToStack(sta, 2, 2);
	// printElementsInStack(sta);
	// int x, y;
	// popFromStack(sta, &x, &y);
	// printf("x = %d, y = %d\n", x, y);
	// pushToStack(sta, 3, 3);
	// printElementsInStack(sta);

	printf("numbers of days that all oranges are rotten = %d\n", orangesRotting(grid, gridSize, gridColSize));
	return 0;
}