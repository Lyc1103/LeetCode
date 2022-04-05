#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct queueInformation
{
	int front, rear;
	int **pos;
} Queue;

Queue *createQueue(int size)
{
	Queue *que = (Queue *)malloc(sizeof(Queue));
	que->front = -1;
	que->rear = -1;
	que->pos = (int **)malloc(2 * sizeof(int *));
	que->pos[0] = (int *)malloc(size * sizeof(int));
	que->pos[1] = (int *)malloc(size * sizeof(int));
	return que;
}

_Bool isEmptyQueue(Queue *que)
{
	return que->front == que->rear ? 1 : 0;
}

void enQueue(Queue *que, int pos_x, int pos_y)
{
	(que->rear)++;
	que->pos[0][que->rear] = pos_x;
	que->pos[1][que->rear] = pos_y;
	return;
}

void deQueue(Queue *que, int *ret_x, int *ret_y)
{
	(que->front)++;
	*ret_x = que->pos[0][que->front];
	*ret_y = que->pos[1][que->front];
	return;
}

int shortestPathBinaryMatrix(int **grid, int gridSize, int *gridColSize)
{
	if (grid[0][0] || grid[gridSize - 1][gridColSize[0] - 1])
		return -1;

	Queue *q = createQueue(gridSize * gridColSize[0] + 1);
	grid[0][0] = 1;
	enQueue(q, 0, 0);

	int cur_x, cur_y;
	while (!isEmptyQueue(q))
	{
		deQueue(q, &cur_x, &cur_y);
		// printf("cur_x = %d, cur_y = %d\n",cur_x, cur_y);
		if (cur_x == gridSize - 1 && cur_y == gridColSize[0] - 1)
			return grid[gridSize - 1][gridColSize[0] - 1];

		// ES
		if (cur_x + 1 < gridSize && cur_y + 1 < gridColSize[0] && grid[cur_x + 1][cur_y + 1] == 0)
		{
			grid[cur_x + 1][cur_y + 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x + 1, cur_y + 1);
		}
		// S
		if (cur_x + 1 < gridSize && grid[cur_x + 1][cur_y] == 0)
		{
			grid[cur_x + 1][cur_y] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x + 1, cur_y);
		}
		// E
		if (cur_y + 1 < gridColSize[0] && grid[cur_x][cur_y + 1] == 0)
		{
			grid[cur_x][cur_y + 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x, cur_y + 1);
		}
		// WS
		if (cur_x + 1 < gridSize && cur_y > 0 && grid[cur_x + 1][cur_y - 1] == 0)
		{
			grid[cur_x + 1][cur_y - 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x + 1, cur_y - 1);
		}
		// EN
		if (cur_x > 0 && cur_y + 1 < gridColSize[0] && grid[cur_x - 1][cur_y + 1] == 0)
		{
			grid[cur_x - 1][cur_y + 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x - 1, cur_y + 1);
		}
		// W
		if (cur_y > 0 && grid[cur_x][cur_y - 1] == 0)
		{
			grid[cur_x][cur_y - 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x, cur_y - 1);
		}
		// N
		if (cur_x > 0 && grid[cur_x - 1][cur_y] == 0)
		{
			grid[cur_x - 1][cur_y] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x - 1, cur_y);
		}
		// WN
		if (cur_x > 0 && cur_y > 0 && grid[cur_x - 1][cur_y - 1] == 0)
		{
			grid[cur_x - 1][cur_y - 1] = grid[cur_x][cur_y] + 1;
			enQueue(q, cur_x - 1, cur_y - 1);
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