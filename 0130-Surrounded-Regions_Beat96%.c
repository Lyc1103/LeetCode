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

void printElementsInStack(Stack *sta)
{
	if (isEmptyStack(sta))
	{
		puts("sta: []");
		return;
	}
	printf("sta: [");
	for (int i = 0; i < sta->top; i++)
		printf("(%d, %d), ", sta->pos[0][i], sta->pos[1][i]);
	printf("(%d, %d)]\n", sta->pos[0][sta->top], sta->pos[1][sta->top]);
	return;
}

void DFSFilledX(char **board, int boardSize, int boardColSize, int cur_x, int cur_y, Stack *sta)
{
	board[cur_x][cur_y] = 'V';
	pushToStack(sta, cur_x, cur_y);
	while (!isEmptyStack(sta))
	{
		popFromStack(sta, &cur_x, &cur_y);
		if (cur_x > 0 && board[cur_x - 1][cur_y] == 'O')
		{
			board[cur_x - 1][cur_y] = 'V';
			pushToStack(sta, cur_x - 1, cur_y);
		}
		if (cur_x + 1 < boardSize && board[cur_x + 1][cur_y] == 'O')
		{
			board[cur_x + 1][cur_y] = 'V';
			pushToStack(sta, cur_x + 1, cur_y);
		}
		if (cur_y > 0 && board[cur_x][cur_y - 1] == 'O')
		{
			board[cur_x][cur_y - 1] = 'V';
			pushToStack(sta, cur_x, cur_y - 1);
		}
		if (cur_y + 1 < boardColSize && board[cur_x][cur_y + 1] == 'O')
		{
			board[cur_x][cur_y + 1] = 'V';
			pushToStack(sta, cur_x, cur_y + 1);
		}
	}
	return;
}

void solve(char **board, int boardSize, int *boardColSize)
{
	int i, j, limit_i = boardSize - 1, limit_j = boardColSize[0] - 1;
	Stack *sta = createStack(boardSize * boardColSize[0]);
	for (i = 0; i <= limit_i; i++)
	{
		if (board[i][0] == 'O')
			DFSFilledX(board, boardSize, boardColSize[0], i, 0, sta);
		if (board[i][limit_j] == 'O')
			DFSFilledX(board, boardSize, boardColSize[0], i, limit_j, sta);
	}
	for (j = 1; j < limit_j; j++)
	{
		if (board[0][j] == 'O')
			DFSFilledX(board, boardSize, boardColSize[0], 0, j, sta);
		if (board[limit_i][j] == 'O')
			DFSFilledX(board, boardSize, boardColSize[0], limit_i, j, sta);
	}
	for (i = 0; i < boardSize; i++)
		for (j = 0; j < boardColSize[0]; j++)
			if (board[i][j] == 'V')
				board[i][j] = 'O';
			else if (board[i][j] == 'O')
				board[i][j] = 'X';

	return;
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
		puts("grid:\n  []");
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
	if ((pfile = fopen("130.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int boardSize, *boardColSize;
	char **board = dealWithInputFile_forGrid(pfile, &boardSize, &boardColSize);
	printGrid(board, boardSize, boardColSize[0]);

	solve(board, boardSize, boardColSize);
	puts("solved");
	printGrid(board, boardSize, boardColSize[0]);

	return 0;
}