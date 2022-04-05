#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackInformation
{
	int top;
	int **land_pos;
} Stack;

Stack *createStack(int size)
{
	Stack *sta = (Stack *)malloc(sizeof(Stack));
	sta->top = -1;
	sta->land_pos = (int **)malloc(2 * sizeof(int *));
	sta->land_pos[0] = (int *)malloc(size * sizeof(int));
	sta->land_pos[1] = (int *)malloc(size * sizeof(int));
	return sta;
}

_Bool isEmptyStack(Stack *sta)
{
	return sta->top == -1 ? 1 : 0;
}

void pushToStack(Stack *sta, int x, int y)
{
	sta->top++;
	sta->land_pos[0][sta->top] = x;
	sta->land_pos[1][sta->top] = y;
	return;
}

void popFromStack(Stack *sta, int *ret_x, int *ret_y)
{
	*ret_x = sta->land_pos[0][sta->top];
	*ret_y = sta->land_pos[1][sta->top];
	(sta->top)--;
	return;
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
		printf("(%d, %d), ", sta->land_pos[0][i], sta->land_pos[1][i]);
	printf("(%d, %d)]\n", sta->land_pos[0][sta->top], sta->land_pos[1][sta->top]);
	return;
}

void freeStack(Stack *sta)
{
	free(sta->land_pos[0]);
	free(sta->land_pos[1]);
	free(sta->land_pos);
	free(sta);
	return;
}

void DFSFilledWater(char **grid, int gridSize, int gridColSize, int cur_x, int cur_y, Stack *sta)
{
	pushToStack(sta, cur_x, cur_y);
	while (!isEmptyStack(sta))
	{
		popFromStack(sta, &cur_x, &cur_y);
		// if (cur_x < 0 || cur_x >= gridSize || cur_y < 0 || cur_y >= gridColSize || grid[cur_x][cur_y] == '0')
		// 	continue;
		// grid[cur_x][cur_y] = '0';
		// pushToStack(sta, cur_x - 1, cur_y);
		// pushToStack(sta, cur_x + 1, cur_y);
		// pushToStack(sta, cur_x, cur_y - 1);
		// pushToStack(sta, cur_x, cur_y + 1);
		if (cur_x > 0 && grid[cur_x - 1][cur_y] == '1')
		{
			grid[cur_x - 1][cur_y] = '0';
			pushToStack(sta, cur_x - 1, cur_y);
		}
		if (cur_x + 1 < gridSize && grid[cur_x + 1][cur_y] == '1')
		{
			grid[cur_x + 1][cur_y] = '0';
			pushToStack(sta, cur_x + 1, cur_y);
		}
		if (cur_y > 0 && grid[cur_x][cur_y - 1] == '1')
		{
			grid[cur_x][cur_y - 1] = '0';
			pushToStack(sta, cur_x, cur_y - 1);
		}
		if (cur_y + 1 < gridColSize && grid[cur_x][cur_y + 1] == '1')
		{
			grid[cur_x][cur_y + 1] = '0';
			pushToStack(sta, cur_x, cur_y + 1);
		}
	}
	return;
}

int numIslands(char **grid, int gridSize, int *gridColSize)
{
	int nums_islands = 0;
	Stack *sta = createStack(gridSize * gridColSize[0]);
	for (int i = 0; i < gridSize; i++)
		for (int j = 0; j < gridColSize[0]; j++)
			if (grid[i][j] == '1')
			{
				DFSFilledWater(grid, gridSize, gridColSize[0], i, j, sta);
				nums_islands++;
			}
	return nums_islands;
}

char **dealWithInputFile_forGrid(FILE *pfile, int *gridSize, int **gridColSize)
{
	int size = 10;
	char **grid = (char **)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++)
	{
		grid[i] = (char *)malloc(size * sizeof(char));
		*gridColSize = (int *)calloc(size, sizeof(int));
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
			fscanf(pfile, "\"%c\"", &grid[*gridSize][ctr]);
			printf("\"%c\"", grid[*gridSize][ctr]);
			ctr++;
			fscanf(pfile, "%c", &c);
			printf("%c", c);
			if (c == ']')
			{
				(*gridColSize)[*gridSize] = ctr;
				(*gridSize)++;
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
	return grid;
}

void printGrid(char **grid, int gridSize, int gridColSize)
{
	if (gridSize == 0)
		puts("grid:\n     []");
	else
	{
		printf("grid: ");
		for (int i = 0; i < gridColSize; i++)
			printf("   %d", i);
		puts("");
		for (int i = 0; i < gridSize; i++)
		{
			printf("     %d [", i);
			for (int j = 0; j < gridColSize - 1; j++)
				printf("\"%c\",", grid[i][j]);
			printf("\"%c\"]\n", grid[i][gridColSize - 1]);
		}
	}
	puts("     completely print.");
	return;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("200.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int gridSize, *gridColSize;
	char **grid = dealWithInputFile_forGrid(pfile, &gridSize, &gridColSize);
	printGrid(grid, gridSize, gridColSize[0]);

	printf("\nnumbers of islands = %d\n", numIslands(grid, gridSize, gridColSize));
	// puts("water-filled grid:");
	// printGrid(grid, gridSize, gridColSize[0]);

	return 0;
}
