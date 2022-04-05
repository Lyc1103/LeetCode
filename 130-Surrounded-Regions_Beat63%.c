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

void DFSFilledX(char **board, int boardSize, int boardColSize, int cur_x, int cur_y, Stack *sta, _Bool **isVisited)
{
	isVisited[cur_x][cur_y] = 1;
	pushToStack(sta, cur_x, cur_y);
	while (!isEmptyStack(sta))
	{
		printElementsInStack(sta);
		popFromStack(sta, &cur_x, &cur_y);
		if (cur_x > 0 && board[cur_x - 1][cur_y] == 'O' && !isVisited[cur_x - 1][cur_y])
		{
			isVisited[cur_x - 1][cur_y] = 1;
			pushToStack(sta, cur_x - 1, cur_y);
		}
		if (cur_x + 1 < boardSize && board[cur_x + 1][cur_y] == 'O' && !isVisited[cur_x + 1][cur_y])
		{
			isVisited[cur_x + 1][cur_y] = 1;
			pushToStack(sta, cur_x + 1, cur_y);
		}
		if (cur_y > 0 && board[cur_x][cur_y - 1] == 'O' && !isVisited[cur_x][cur_y - 1])
		{
			isVisited[cur_x][cur_y - 1] = 1;
			pushToStack(sta, cur_x, cur_y - 1);
		}
		if (cur_y + 1 < boardColSize && board[cur_x][cur_y + 1] == 'O' && !isVisited[cur_x][cur_y + 1])
		{
			isVisited[cur_x][cur_y + 1] = 1;
			pushToStack(sta, cur_x, cur_y + 1);
		}
	}
	puts("");
	return;
}

void solve(char **board, int boardSize, int *boardColSize)
{
	int i, j, limit_i = boardSize - 1, limit_j = boardColSize[0] - 1;
	Stack *sta = createStack(boardSize * boardColSize[0]);
	_Bool **isVisited = (_Bool **)malloc(boardSize * sizeof(_Bool *));
	for (i = 0; i < boardSize; i++)
		isVisited[i] = (_Bool *)calloc(boardColSize[0], sizeof(_Bool));

	for (i = 0; i <= limit_i; i++)
	{
		if (board[i][0] == 'O' && !isVisited[i][0])
			DFSFilledX(board, boardSize, boardColSize[0], i, 0, sta, isVisited);
		if (board[i][limit_j] == 'O' && !isVisited[i][limit_j])
			DFSFilledX(board, boardSize, boardColSize[0], i, limit_j, sta, isVisited);
	}
	for (j = 1; j < limit_j; j++)
	{
		if (board[0][j] == 'O' && !isVisited[0][j])
			DFSFilledX(board, boardSize, boardColSize[0], 0, j, sta, isVisited);
		if (board[limit_i][j] == 'O' && !isVisited[limit_i][j])
			DFSFilledX(board, boardSize, boardColSize[0], limit_i, j, sta, isVisited);
	}
	for (i = 1; i < limit_i; i++)
		for (j = 1; j < limit_j; j++)
			if (board[i][j] == 'O' && !isVisited[i][j])
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