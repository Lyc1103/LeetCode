#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct queueInformation
{
	int front, rear;
	int **position;
} Queue;

Queue *createQueue(int size)
{
	Queue *que = (Queue *)malloc(sizeof(Queue));
	que->front = -1;
	que->rear = -1;
	que->position = (int **)malloc(2 * sizeof(int *));
	que->position[0] = (int *)calloc(size, sizeof(int));
	que->position[1] = (int *)calloc(size, sizeof(int));
	return que;
}

_Bool isEmptyQueue(Queue *que)
{
	if (que->front == que->rear)
		return 1;
	return 0;
}

void EnQueue(Queue *que, int x, int y)
{
	(que->rear)++;
	que->position[0][que->rear] = x;
	que->position[1][que->rear] = y;
	return;
}

void DeQueue(Queue *que, int *x, int *y)
{
	if (isEmptyQueue(que))
	{
		puts("Queue is empty. DeQueue error!");
		exit(0);
	}
	(que->front)++;
	*x = que->position[0][que->front];
	*y = que->position[1][que->front];
	return;
}

void freeQueue(Queue *que)
{
	free(que->position[0]);
	free(que->position[1]);
	free(que->position);
	free(que);
	return;
}

void printElementsInQueue(Queue *que)
{
	if (isEmptyQueue(que))
	{
		printf("front = %d, rear = %d, que = []\n", que->front, que->rear);
		return;
	}
	printf("front = %d, rear = %d, que = [", que->front, que->rear);
	int i;
	for (i = que->front + 1; i < que->rear; i++)
		printf("(%d,%d), ", que->position[0][i], que->position[1][i]);
	printf("(%d,%d)]\n", que->position[0][i], que->position[1][i]);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **updateMatrix(int **mat, int matSize, int *matColSize, int *returnSize, int **returnColumnSizes)
{
	*returnSize = matSize;
	*returnColumnSizes = (int *)malloc(matSize * sizeof(int));
	int **ret = (int **)malloc(matSize * sizeof(int *));
	_Bool **isVisited = (_Bool **)malloc(matSize * sizeof(_Bool *));
	for (int i = 0; i < matSize; i++)
	{
		(*returnColumnSizes)[i] = matColSize[i];
		ret[i] = (int *)calloc(matColSize[0], sizeof(int));
		isVisited[i] = (_Bool *)calloc(matColSize[0], sizeof(_Bool));
	}

	Queue *que = createQueue(matSize * matColSize[0]);
	for (int i = 0; i < matSize; i++)
		for (int j = 0; j < *matColSize; j++)
			if (mat[i][j] == 0)
			{
				isVisited[i][j] = 1;
				EnQueue(que, i, j);
			}
	int cur_x, cur_y;
	while (!isEmptyQueue(que))
	{
		DeQueue(que, &cur_x, &cur_y);
		if (cur_x > 0 && !isVisited[cur_x - 1][cur_y])
		{
			ret[cur_x - 1][cur_y] = ret[cur_x][cur_y] + 1;
			isVisited[cur_x - 1][cur_y] = 1;
			EnQueue(que, cur_x - 1, cur_y);
		}
		if (cur_x + 1 < matSize && !isVisited[cur_x + 1][cur_y])
		{
			ret[cur_x + 1][cur_y] = ret[cur_x][cur_y] + 1;
			isVisited[cur_x + 1][cur_y] = 1;
			EnQueue(que, cur_x + 1, cur_y);
		}
		if (cur_y > 0 && !isVisited[cur_x][cur_y - 1])
		{
			ret[cur_x][cur_y - 1] = ret[cur_x][cur_y] + 1;
			isVisited[cur_x][cur_y - 1] = 1;
			EnQueue(que, cur_x, cur_y - 1);
		}
		if (cur_y + 1 < matColSize[0] && !isVisited[cur_x][cur_y + 1])
		{
			ret[cur_x][cur_y + 1] = ret[cur_x][cur_y] + 1;
			isVisited[cur_x][cur_y + 1] = 1;
			EnQueue(que, cur_x, cur_y + 1);
		}
	}

	freeQueue(que);
	return ret;
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
	if ((pfile = fopen("542.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	int matSize, *matColSize;
	int **mat = dealWithInputFile_forMatrix(pfile, &matSize, &matColSize);
	printf("matSize = %d, matColSize = %d\n", matSize, matColSize[0]);
	puts("matrix:");
	printMatrix(mat, matSize, matColSize[0]);

	int **ret, returnSize, *returnColumnSize;
	ret = updateMatrix(mat, matSize, matColSize, &returnSize, &returnColumnSize);

	puts("updated matrix:");
	printMatrix(ret, matSize, matColSize[0]);

	return 0;
}